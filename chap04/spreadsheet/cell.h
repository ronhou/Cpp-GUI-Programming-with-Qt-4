#ifndef CELL_H
#define CELL_H

#include <QTableWidgetItem>

class Cell : public QTableWidgetItem
{
public:
    Cell();

	QString formula() const;
	void setFormula(const QString& formula);
};

#endif // CELL_H
