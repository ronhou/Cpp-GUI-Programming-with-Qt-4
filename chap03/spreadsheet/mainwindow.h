#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Spreadsheet;
class FindDialog;
class QAction;
class QMenu;
class QToolBar;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void find();
    void goToCell();
    void sort();
    void about();
    void openRecentFile();

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
    QStringList recentFiles;
    QString curFile;

    enum { MaxRecentFiles = 5 };
    QAction *recentFileActions[MaxRecentFiles];
    QAction *sepratorAction;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *selectSubMenu;
    QMenu *toolsMenu;
    QMenu *optionsMenu;
    QMenu *helpMenu;
    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *exitAction;
    QAction *cutAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *deleteAction;
    QAction *selectRowAction;
    QAction *selectColumnAction;
    QAction *selectAllAction;
    QAction *findAction;
    QAction *goToCellAction;
    QAction *recalculateAction;
    QAction *sortAction;
    QAction *showGridAction;
    QAction *autoRecalcAction;
    QAction *aboutAction;
    QAction *aboutQtAction;
};
#endif // MAINWINDOW_H
