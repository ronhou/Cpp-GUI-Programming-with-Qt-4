#include <QApplication>
#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <QMessageBox>

#include "cell.h"
#include "spreadsheet.h"

Spreadsheet::Spreadsheet(QWidget *parent)
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
}

void Spreadsheet::copy()
{
	qDebug() << "copy in spreadsheet";
}

void Spreadsheet::paste()
{
	qDebug() << "paste in spreadsheet";
}

void Spreadsheet::del()
{
	qDebug() << "delete in spreadsheet";
}

void Spreadsheet::selectCurrentRow()
{
	qDebug() << "select current row";
}

void Spreadsheet::selectCurrentColumn()
{
	qDebug() << "select current column";
}

void Spreadsheet::recalculate()
{
	qDebug() << "do recalculate";
}

void Spreadsheet::setAutoRecalculate(bool recalc)
{
	autoRecalc = recalc;
	if (autoRecalc)
		recalculate();
}

void Spreadsheet::findNext(const QString &str, Qt::CaseSensitivity cs)
{
	qDebug() << "find next text" << str << cs;
}

void Spreadsheet::findPrev(const QString &str, Qt::CaseSensitivity cs)
{
	qDebug() << "find previous text" << str << cs;
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

void Spreadsheet::sort(const SpreadsheetCompare &compare)
{
	qDebug() << "sort spreadsheet";
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
