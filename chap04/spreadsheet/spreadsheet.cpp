#include <QApplication>
#include <QClipboard>
#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <QMessageBox>

#include "cell.h"
#include "spreadsheet.h"

bool SpreadsheetCompare::operator()(const QStringList& row1,
									const QStringList& row2) const
{
	for (int i = 0; i < KeyCount; ++i) {
		int column = keys[i];
		if (column != -1) {
			if (row1[column] != row2[column]) {
				if (ascending[i]) {
					return row1[column] < row2[column];
				} else {
					return row1[column] > row2[column];
				}
			}
		}
	}
	return false;
}

Spreadsheet::Spreadsheet(QWidget* parent)
	: QTableWidget(parent)
{
	autoRecalc = true;

	setItemPrototype(new Cell);
	setSelectionMode(ContiguousSelection);

	connect(this,
			SIGNAL(itemChanged(QTableWidgetItem*)),
			this,
			SLOT(somethingChanged()));

	clear();
}

void Spreadsheet::cut()
{
	qDebug() << "cut in spreadsheet";
	copy();
	del();
}

void Spreadsheet::copy()
{
	qDebug() << "copy in spreadsheet";
	QTableWidgetSelectionRange range = selectedRange();
	QString text;
	for (int i = 0; i < range.rowCount(); ++i) {
		if (i > 0)
			text += "\n";
		for (int j = 0; j < range.columnCount(); ++j) {
			if (j > 0)
				text += "\t";
			text += formula(range.topRow() + i, range.leftColumn() + j);
		}
	}
	QApplication::clipboard()->setText(text);
}

void Spreadsheet::paste()
{
	qDebug() << "paste in spreadsheet";
	QTableWidgetSelectionRange range = selectedRange();
	QString text = QApplication::clipboard()->text();
	QStringList rows = text.trimmed().split('\n');
	int numRows = rows.size();
	int numColumns = rows.first().count('\t') + 1;

	if (range.rowCount() * range.columnCount() != 1
		&& (range.rowCount() != numRows || range.columnCount() != numColumns)) {
		QMessageBox::information(
			this,
			tr("Spreadsheet"),
			tr("The information cannot be pasted because the copy and paste "
			   "areas aren't the same size."));
		return;
	}

	for (int i = 0; i < numRows; ++i) {
		QStringList cells = rows[i].split('\t');
		for (int j = 0; j < numColumns; ++j) {
			int row = range.topRow() + i;
			int column = range.leftColumn() + j;
			if (row < rowCount() && column < columnCount())
				setFormula(range.topRow() + i, range.leftColumn() + j, cells[j]);
		}
	}
	somethingChanged();
}

void Spreadsheet::del()
{
	qDebug() << "delete in spreadsheet";
	QList<QTableWidgetItem*> items = selectedItems();
	if (!items.empty()) {
		foreach (QTableWidgetItem* item, items) {
			delete item;
		}
		somethingChanged();
	}
}

void Spreadsheet::selectCurrentRow()
{
	qDebug() << "select current row";
	selectRow(currentRow());
}

void Spreadsheet::selectCurrentColumn()
{
	qDebug() << "select current column";
	selectColumn(currentColumn());
}

void Spreadsheet::recalculate()
{
	qDebug() << "do recalculate";
	for (int i = 0; i < rowCount(); ++i) {
		for (int j = 0; j < columnCount(); ++j) {
			Cell* c = cell(i, j);
			if (c)
				c->setDirty();
		}
	}
	viewport()->update();
}

void Spreadsheet::setAutoRecalculate(bool recalc)
{
	autoRecalc = recalc;
	if (autoRecalc)
		recalculate();
}

void Spreadsheet::findNext(const QString& str, Qt::CaseSensitivity cs)
{
	qDebug() << "find next text" << str << cs;
	int row = currentRow();
	int column = currentColumn() + 1;
	while (row < rowCount()) {
		while (column < columnCount()) {
			if (text(row, column).contains(str, cs)) {
				clearSelection();
				setCurrentCell(row, column);
				activateWindow();
				return;
			}
			++column;
		}
		++row;
		column = 0;
	}
	QApplication::beep();
}

void Spreadsheet::findPrev(const QString& str, Qt::CaseSensitivity cs)
{
	qDebug() << "find previous text" << str << cs;
	int row = currentRow();
	int column = currentColumn() - 1;
	while (row >= 0) {
		while (column >= 0) {
			if (text(row, column).contains(str, cs)) {
				clearSelection();
				setCurrentCell(row, column);
				activateWindow();
				return;
			}
			--column;
		}
		--row;
		column = columnCount() - 1;
	}
	QApplication::beep();
}

void Spreadsheet::somethingChanged()
{
	if (autoRecalc)
		recalculate();
	emit modified();
}

QString Spreadsheet::currentLocation() const
{
	return QChar('A' + currentColumn()) + QString::number(currentRow() + 1);
}

QString Spreadsheet::currentFormula() const
{
	return formula(currentRow(), currentColumn());
}

void Spreadsheet::clear()
{
	qDebug() << "clear Spreadsheet";
	setRowCount(0);
	setColumnCount(0);
	setRowCount(RowCount);
	setColumnCount(ColumnCount);

	for (int i = 0; i < ColumnCount; ++i) {
		QTableWidgetItem* item = new QTableWidgetItem;
		item->setText(QString(QChar('A' + i)));
		setHorizontalHeaderItem(i, item);
	}

	setCurrentCell(0, 0);
}

bool Spreadsheet::readFile(const QString& fileName)
{
	qDebug() << "read spreadsheet file" << fileName;
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly)) {
		QMessageBox::warning(this,
							 tr("Spreadsheet"),
							 tr("Cannot read file %1: \n%2")
								 .arg(file.fileName(), file.errorString()));
		return false;
	}

	QDataStream in(&file);
	in.setVersion(QDataStream::Qt_4_3);

	quint32 magicNum;
	in >> magicNum;
	if (magicNum != MagicNumber) {
		QMessageBox::warning(this,
							 tr("Spreadsheet"),
							 tr("The file is not a Spreadsheet file."));
		return false;
	}

	clear();

	quint16 row = 0;
	quint16 column = 0;
	QString str;

	QApplication::setOverrideCursor(Qt::WaitCursor);
	while (!in.atEnd()) {
		in >> row >> column >> str;
		setFormula(row, column, str);
	}
	QApplication::restoreOverrideCursor();
	return true;
}

bool Spreadsheet::writeFile(const QString& fileName)
{
	qDebug() << "write spreadsheet file" << fileName;

	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly)) {
		QMessageBox::warning(this,
							 tr("Spreadsheet"),
							 tr("Cannot write file %1:\n%2")
								 .arg(file.fileName(), file.errorString()));
		return false;
	}

	QDataStream out(&file);
	out.setVersion(QDataStream::Qt_4_3);

	out << quint32(MagicNumber);

	int curRowCount = rowCount();
	int curColumnCount = columnCount();
	QApplication::setOverrideCursor(Qt::WaitCursor);
	for (int row = 0; row < curRowCount; ++row) {
		for (int column = 0; column < curColumnCount; ++column) {
			QString str = formula(row, column);
			if (!str.isEmpty())
				out << quint16(row) << quint16(column) << str;
		}
	}
	QApplication::restoreOverrideCursor();
	return true;
}

QTableWidgetSelectionRange Spreadsheet::selectedRange() const
{
	QList<QTableWidgetSelectionRange> ranges = selectedRanges();
	return ranges.isEmpty() ? QTableWidgetSelectionRange() : ranges.first();
}

void Spreadsheet::sort(const SpreadsheetCompare& compare)
{
	qDebug() << "sort spreadsheet";
	QTableWidgetSelectionRange range = selectedRange();

	QList<QStringList> rows;
	for (int i = 0; i < range.rowCount(); ++i) {
		QStringList row;
		for (int j = 0; j < columnCount(); ++j) {
			row.append(formula(range.topRow() + i, range.leftColumn() + j));
		}
		rows.append(row);
	}

	qStableSort(rows.begin(), rows.end(), compare);

	for (int i = 0; i < range.rowCount(); ++i) {
		for (int j = 0; j < range.columnCount(); ++j) {
			setFormula(range.topRow() + i, range.leftColumn() + j, rows[i][j]);
		}
	}

	clearSelection();
	somethingChanged();
}

Cell* Spreadsheet::cell(int row, int column) const
{
	return static_cast<Cell*>(item(row, column));
}

QString Spreadsheet::text(int row, int column) const
{
	Cell* c = cell(row, column);
	if (c) {
		return c->text();
	} else {
		return "";
	}
}

QString Spreadsheet::formula(int row, int column) const
{
	Cell* c = cell(row, column);
	if (c) {
		return c->formula();
	} else {
		return "";
	}
}

void Spreadsheet::setFormula(int row, int column, const QString& formula)
{
	Cell* c = cell(row, column);
	if (!c) {
		c = new Cell;
		setItem(row, column, c);
	}
	c->setFormula(formula);
}
