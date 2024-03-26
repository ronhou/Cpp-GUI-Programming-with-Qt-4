#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Spreadsheet;
class FindDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createActions();
    void createMenus();
    void createContextMenu();
    void createToolBars();
    void createStatusBar();
    void readSettings();
    void setCurrentFile(const QString &fileName);

private:
    Spreadsheet *spreadsheet;
    FindDialog *findDialog;
    QString curFile;
};
#endif // MAINWINDOW_H
