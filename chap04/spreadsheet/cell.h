#ifndef CELL_H
#define CELL_H

#include <QTableWidgetItem>

class Cell : public QTableWidgetItem
{
public:
	Cell();

	QTableWidgetItem* clone() const;
	QVariant data(int role) const;
	void setData(int role, const QVariant& value);
	QString formula() const;
	void setFormula(const QString& formula);
	void setDirty();

private:
	QVariant value() const;
	QVariant evalExpression(const QString& str, int& pos) const;
	QVariant evalTerm(const QString& str, int& pos) const;
	QVariant evalFactor(const QString& str, int& pos) const;

private:
	mutable bool cacheIsDirty;
	mutable QVariant cachedValue;
};

#endif // CELL_H
