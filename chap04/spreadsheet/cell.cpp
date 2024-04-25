#include "cell.h"

Cell::Cell() {}

QString Cell::formula() const
{
	return data(Qt::EditRole).toString();
}

void Cell::setFormula(const QString& formula)
{
	setData(Qt::EditRole, formula);
}

void Cell::setDirty()
{
	cacheIsDirty = true;
}
