#include <QDebug>

#include "spreadsheet.h"

Spreadsheet::Spreadsheet(QWidget *parent)
	: QTableWidget(parent)
{
	autoRecalc = true;
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

QString Spreadsheet::currentLocation() const
{
	return QChar('A' + currentColumn()) + QString::number(currentRow() + 1);
}

QString Spreadsheet::currentFormula() const
{
	return "";
}

bool Spreadsheet::readFile(const QString &fileName)
{
	qDebug() << "read spreadsheet file" << fileName;
	return true;
}

bool Spreadsheet::writeFile(const QString &fileName)
{
	qDebug() << "write spreadsheet file" << fileName;
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
