#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <QTableWidget>

class SpreadsheetCompare
{
public:
    enum { KeyCount = 3 };
    int keys[KeyCount];
    bool ascending[KeyCount];
};

class Spreadsheet : public QTableWidget
{
    Q_OBJECT
public:
    Spreadsheet(QWidget *parent = nullptr);

    bool autoRecalculate() const { return autoRecalc; }
    QString currentLocation() const;
    QString currentFormula() const;
    bool readFile(const QString& fileName);
    bool writeFile(const QString& fileName);
    QTableWidgetSelectionRange selectedRange() const;
    void sort(const SpreadsheetCompare& compare);

private slots:
    void cut();
    void copy();
    void paste();
    void del();
    void selectCurrentRow();
    void selectCurrentColumn();
    void recalculate();
    void setAutoRecalculate(bool recalc);
    void findNext(const QString &str,Qt::CaseSensitivity cs);
    void findPrev(const QString &str,Qt::CaseSensitivity cs);

private:
    bool autoRecalc;
};

#endif // SPREADSHEET_H
