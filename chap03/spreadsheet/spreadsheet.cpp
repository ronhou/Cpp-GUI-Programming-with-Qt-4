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
