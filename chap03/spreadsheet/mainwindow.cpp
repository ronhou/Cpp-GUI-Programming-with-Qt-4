#include <QDebug>
#include <QApplication>
#include <QAction>
#include <QIcon>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>

#include "mainwindow.h"
#include "spreadsheet.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , findDialog(nullptr)
{
    spreadsheet = new Spreadsheet;
    setCentralWidget(spreadsheet);

    createActions();
    createMenus();
    createContextMenu();
    createToolBars();
    createStatusBar();

    readSettings();

    findDialog = nullptr;

    setWindowIcon(QIcon(":/images/icon.png"));
    setCurrentFile("");
}

MainWindow::~MainWindow() {}

void MainWindow::createActions()
{
    newAction = new QAction(tr("&New"), this);
    newAction->setIcon(QIcon(":/images/new.png"));
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("Create a new spreadsheet file"));
    connect(newAction, SIGNAL(triggered(bool)), this, SLOT(newFile()));

    openAction = new QAction(tr("&Open"), this);
    openAction->setIcon(QIcon(":/images/open.png"));
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing spreadsheet file"));
    connect(openAction, SIGNAL(triggered(bool)), this, SLOT(open()));

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setIcon(QIcon(":/images/save.png"));
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save the spreadsheet to disk"));
    connect(saveAction, SIGNAL(triggered(bool)), this, SLOT(save()));

    saveAsAction = new QAction(tr("Save &As..."), this);
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    saveAsAction->setStatusTip(tr("Save the spreadsheet under a new name"));
    connect(saveAsAction, SIGNAL(triggered(bool)), this, SLOT(saveAs()));

    for (int i = 0; i < MaxRecentFiles; ++i) {
        // 显示文本呢？
        recentFileActions[i] = new QAction(this);
        recentFileActions[i]->setVisible(false);
        connect(recentFileActions[i], SIGNAL(triggered(bool)), this, SLOT(openRecentFile()));
    }

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, SIGNAL(triggered(bool)), this, SLOT(close()));

    cutAction = new QAction(tr("Cu&t"), this);
    cutAction->setIcon(QIcon(":/images/cut.png"));
    cutAction->setShortcut(QKeySequence::Cut);
    cutAction->setStatusTip(tr("Cut the current selection's contents to the clipboard"));
    connect(cutAction, SIGNAL(triggered(bool)), spreadsheet, SLOT(cut()));

    copyAction = new QAction(tr("&Copy"), this);
    copyAction->setIcon(QIcon(":/images/copy.png"));
    copyAction->setShortcut(QKeySequence::Copy);
    copyAction->setStatusTip(tr("Copy the current selection's contents to the clipboard"));
    connect(copyAction, SIGNAL(triggered(bool)), spreadsheet, SLOT(copy()));

    pasteAction = new QAction(tr("&Paste"), this);
    pasteAction->setIcon(QIcon(":/images/paste.png"));
    pasteAction->setShortcut(QKeySequence::Paste);
    pasteAction->setStatusTip(tr("Paste the clipboard's contents into the current selection"));
    connect(pasteAction, SIGNAL(triggered(bool)), spreadsheet, SLOT(paste()));

    deleteAction = new QAction(tr("&Delete"), this);
    deleteAction->setShortcut(QKeySequence::Delete);
    deleteAction->setStatusTip(tr("Delete the current selection's contents"));
    connect(deleteAction, SIGNAL(triggered(bool)), spreadsheet, SLOT(del()));

    selectRowAction = new QAction(tr("&Row"), this);
    selectRowAction->setStatusTip(tr("Select all the cells in the current row"));
    connect(selectRowAction, SIGNAL(triggered(bool)), spreadsheet, SLOT(selectCurrentRow()));

    selectColumnAction = new QAction(tr("&Column"), this);
    selectColumnAction->setStatusTip(tr("Select all the cells in the current column"));
    connect(selectColumnAction, SIGNAL(triggered(bool)), spreadsheet, SLOT(selectCurrentColumn()));

    selectAllAction = new QAction(tr("&All"), this);
    selectAllAction->setShortcut(QKeySequence::SelectAll);
    selectAllAction->setStatusTip(tr("Select all the cells in the spreadsheet"));
    connect(selectAllAction, SIGNAL(triggered(bool)), spreadsheet, SLOT(selectAll()));

    findAction = new QAction(tr("&Find..."), this);
    findAction->setIcon(QIcon(":/images/find.png"));
    findAction->setShortcut(QKeySequence::Find);
    findAction->setStatusTip(tr("Find a matching cell"));
    connect(findAction, SIGNAL(triggered(bool)), this, SLOT(find()));

    goToCellAction = new QAction(tr("&Go to Cell..."), this);
    goToCellAction->setIcon(QIcon(":/images/gotocell.png"));
    goToCellAction->setShortcut(tr("Ctrl+G"));
    goToCellAction->setStatusTip(tr("Go to te specified cell"));
    connect(goToCellAction, SIGNAL(triggered(bool)), this, SLOT(goToCell()));

    recalculateAction = new QAction(tr("&Recalculate"), this);
    recalculateAction->setShortcut(tr("F9"));
    recalculateAction->setStatusTip(tr("Recalculate all the spreadsheet's formulas"));
    connect(recalculateAction, SIGNAL(triggered(bool)), spreadsheet, SLOT(recalculate()));

    sortAction = new QAction(tr("&Sort..."), this);
    sortAction->setStatusTip(tr("Sort the selected cells or all the cells"));
    connect(sortAction, SIGNAL(triggered(bool)), this, SLOT(sort()));

    showGridAction = new QAction(tr("&Show Grid"));
    showGridAction->setCheckable(true);
    showGridAction->setChecked(spreadsheet->showGrid());
    showGridAction->setStatusTip(tr("Show or hide the spreadsheet's grid"));
    connect(showGridAction, SIGNAL(toggled(bool)), spreadsheet, SLOT(setShowGrid(bool)));
#if QT_VERSION < 0x040102
    connect(showGridAction, SIGNAL(toggled(bool)), spreadsheet->viewport(), SLOT(update()));
#endif

    autoRecalcAction = new QAction(tr("&Auto-Recalculate"), this);
    autoRecalcAction->setCheckable(true);
    autoRecalcAction->setChecked(spreadsheet->autoRecalculate());
    autoRecalcAction->setStatusTip(tr("Switch auto-recalculation on or off"));
    connect(autoRecalcAction, SIGNAL(toggled(bool)), spreadsheet, SLOT(setAutoRecalculate(bool)));

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("Show the application's About box"));
    connect(aboutAction, SIGNAL(triggered(bool)), this, SLOT(about()));

    aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutAction->setStatusTip(tr("Show the Qt library's about box"));
    connect(aboutQtAction, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    sepratorAction = fileMenu->addSeparator();
    for (int i = 0; i < MaxRecentFiles; ++i)
        fileMenu->addAction(recentFileActions[i]);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addAction(deleteAction);

    selectSubMenu = editMenu->addMenu(tr("&Select"));
    selectSubMenu->addAction(selectRowAction);
    selectSubMenu->addAction(selectColumnAction);
    selectSubMenu->addAction(selectAllAction);

    editMenu->addSeparator();
    editMenu->addAction(findAction);
    editMenu->addAction(goToCellAction);

    toolsMenu = menuBar()->addMenu(tr("&Tools"));
    toolsMenu->addAction(recalculateAction);
    toolsMenu->addAction(sortAction);

    optionsMenu = menuBar()->addMenu(tr("&Options"));
    optionsMenu->addAction(showGridAction);
    optionsMenu->addAction(autoRecalcAction);

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
}

void MainWindow::createContextMenu()
{
    spreadsheet->addAction(cutAction);
    spreadsheet->addAction(copyAction);
    spreadsheet->addAction(pasteAction);
    spreadsheet->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("&File"));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);

    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(cutAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);
    editToolBar->addSeparator();
    editToolBar->addAction(findAction);
    editToolBar->addAction(goToCellAction);
}

void MainWindow::createStatusBar()
{
    qDebug() << "create status bar";
}

void MainWindow::readSettings()
{
    qDebug() << "read settings";
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    qDebug() << "set current file: " << fileName;
}

void MainWindow::newFile()
{
    qDebug() << "create a new spreadsheet file";
}

void MainWindow::open()
{
    qDebug() << "open an existing spreadsheet file";
}

bool MainWindow::save()
{
    qDebug() << "save the spreadsheet to disk";
    return false;
}

bool MainWindow::saveAs()
{
    qDebug() << "save the spreadsheet under a new name";
    return false;
}

void MainWindow::openRecentFile()
{
    qDebug() << "open a rencent file";
}

void MainWindow::find()
{
    qDebug() << "show find dialog";
}

void MainWindow::goToCell()
{
    qDebug() << "show goToCell dialog";
}

void MainWindow::sort()
{
    qDebug() << "show sort dialog";
}

void MainWindow::about()
{
    qDebug() << "show about dialog";
}
