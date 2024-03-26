#include <QDebug>
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
    qDebug() << "create actions";
}

void MainWindow::createMenus()
{
    qDebug() << "create menus";
}

void MainWindow::createContextMenu()
{
    qDebug() << "create context menu";
}

void MainWindow::createToolBars()
{
    qDebug() << "create toobars";
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
