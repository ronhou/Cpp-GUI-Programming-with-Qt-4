#ifndef CELL_H
#define CELL_H

#include <QTableWidgetItem>

class Cell : public QTableWidgetItem
{
public:
    Cell();

	QString formula() const;
	void setFormula(const QString& formula);
	void setDirty();

private:
	bool cacheIsDirty;
};

#endif // CELL_H
