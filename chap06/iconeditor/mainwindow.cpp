#include "mainwindow.h"
#include "iconeditor.h"

#include <QAction>
#include <QDockWidget>
#include <QFontComboBox>
#include <QHeaderView>
#include <QIcon>
#include <QMenuBar>
#include <QScrollArea>
#include <QSettings>
#include <QSpinBox>
#include <QStatusBar>
#include <QToolBar>
#include <QTreeWidget>

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	m_iconEditor = new IconEditor;
	// m_iconEditor->setWindowTitle(QObject::tr("Icon Editor"));
	// m_iconEditor->setWindowIcon(QIcon(":/images/mouse.png"));
	m_iconEditor->setIconImage(QImage(":/images/mouse.png"));
	m_iconEditor->setPenColor(Qt::red);
	m_iconEditor->setZoomFactor(10);

	m_scrollArea = new QScrollArea(this);
	m_scrollArea->setWidget(m_iconEditor);
	m_scrollArea->viewport()->setBackgroundRole(QPalette::Dark);
	m_scrollArea->viewport()->setAutoFillBackground(true);
	// 下面滚动条的策略并没有预想中的生效
	// m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	// m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

	setCentralWidget(m_scrollArea);

	createActions();
	createMenus();
	createToolBars();
	addShapesDocWidget();
	createContextMenu();

	setWindowTitle(tr("Icon Editor"));
	setWindowIcon(QIcon(":/images/mouse.png"));

	readSettings();
}

MainWindow::~MainWindow()
{
	writeSettings();
}

void MainWindow::createActions()
{
	m_newAction = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
	m_openAction = new QAction(QIcon(":/images/open.png"), tr("&Open"), this);
	m_saveAction = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
	m_printAction = new QAction(QIcon(":/images/print.png"), tr("&Print"), this);
	m_cutAction = new QAction(QIcon(":/images/cut.png"), tr("&Cut"), this);
	m_copyAction = new QAction(QIcon(":/images/copy.png"), tr("&Copy"), this);
	m_pasteAction = new QAction(QIcon(":/images/paste.png"), tr("&Paste"), this);
}

void MainWindow::createMenus()
{
	menuBar()->addMenu(tr("&File"));
	menuBar()->addMenu(tr("&Edit"));
	menuBar()->addMenu(tr("&View"));
	menuBar()->addMenu(tr("&Tools"));
	menuBar()->addMenu(tr("&Preferences"));
	menuBar()->addMenu(tr("&Help"));
}

void MainWindow::createToolBars()
{
	m_fileToolBar = addToolBar(tr("&File"));
	m_fileToolBar->setAllowedAreas(Qt::TopToolBarArea);
	m_fileToolBar->addAction(m_newAction);
	m_fileToolBar->addAction(m_openAction);
	m_fileToolBar->addAction(m_saveAction);
	m_fileToolBar->addAction(m_printAction);

	m_editToolBar = addToolBar(tr("&Edit"));
	m_editToolBar->setAllowedAreas(Qt::TopToolBarArea);
	m_editToolBar->addAction(m_cutAction);
	m_editToolBar->addAction(m_copyAction);
	m_editToolBar->addAction(m_pasteAction);

	// fontToolBar
	m_fontToolBar = new QToolBar(tr("Font"));
	m_fontToolBar->setObjectName("fontToolBar");

	QFontComboBox* familyComboBox = new QFontComboBox;
	m_fontToolBar->addWidget(familyComboBox);

	QSpinBox* sizeSpinBox = new QSpinBox;
	m_fontToolBar->addWidget(sizeSpinBox);

	QAction* boldAction = new QAction(QIcon(":/images/bold.png"), tr("Bold"), this);
	QAction* italicAction = new QAction(QIcon(":/images/italic.png"), tr("Italic"), this);
	QAction* underlineAction = new QAction(QIcon(":/images/underline.png"), tr("Underline"), this);
	m_fontToolBar->addAction(boldAction);
	m_fontToolBar->addAction(italicAction);
	m_fontToolBar->addAction(underlineAction);

	m_fontToolBar->setAllowedAreas(Qt::TopToolBarArea);
	addToolBar(m_fontToolBar);
}

void MainWindow::addShapesDocWidget()
{
	QTreeWidget* treeWidget = new QTreeWidget;
	// 隐藏行头
	treeWidget->header()->setVisible(false);
	// 添加项
	QTreeWidgetItem* rectanglesItem = new QTreeWidgetItem(treeWidget);
	rectanglesItem->setText(0, tr("Rectangles"));
	QTreeWidgetItem* squareItem = new QTreeWidgetItem(rectanglesItem);
	squareItem->setText(0, tr("Square"));
	QTreeWidgetItem* generalRectItem = new QTreeWidgetItem(rectanglesItem);
	generalRectItem->setText(0, tr("General Rectangle"));
	QTreeWidgetItem* ellipsesItem = new QTreeWidgetItem(treeWidget);
	ellipsesItem->setText(0, tr("Ellipses"));
	QTreeWidgetItem* circleItem = new QTreeWidgetItem(ellipsesItem);
	circleItem->setText(0, tr("Circle"));
	QTreeWidgetItem* generalEllipsesItem = new QTreeWidgetItem(ellipsesItem);
	generalEllipsesItem->setText(0, tr("General Ellipse"));
	QTreeWidgetItem* miscellaneousItem = new QTreeWidgetItem(treeWidget);
	miscellaneousItem->setText(0, tr("Miscellaneous"));

	m_shapesDocWidget = new QDockWidget(tr("Shapes"));
	m_shapesDocWidget->setObjectName("shapesDocWidget");
	m_shapesDocWidget->setWidget(treeWidget);
	m_shapesDocWidget->setAllowedAreas(Qt::LeftDockWidgetArea
									   | Qt::RightDockWidgetArea);
	addDockWidget(Qt::RightDockWidgetArea, m_shapesDocWidget);

	// setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
	// setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
	// setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
	// setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
}

void MainWindow::createContextMenu()
{
	QAction* shapesAction = new QAction(tr("Shapes"), this);
	shapesAction->setCheckable(true);
	shapesAction->setChecked(true);
	connect(shapesAction, SIGNAL(toggled(bool)), m_shapesDocWidget, SLOT(setVisible(bool)));
	addAction(shapesAction);

	QAction* fileAction = new QAction(tr("File"), this);
	fileAction->setCheckable(true);
	fileAction->setChecked(true);
	connect(fileAction, SIGNAL(toggled(bool)), m_fileToolBar, SLOT(setVisible(bool)));
	addAction(fileAction);

	QAction* editAction = new QAction(tr("Edit"), this);
	editAction->setCheckable(true);
	editAction->setChecked(true);
	connect(editAction, SIGNAL(toggled(bool)), m_editToolBar, SLOT(setVisible(bool)));
	addAction(editAction);

	QAction* fontAction = new QAction(tr("Font"), this);
	fontAction->setCheckable(true);
	fontAction->setChecked(true);
	connect(fontAction, SIGNAL(toggled(bool)), m_fontToolBar, SLOT(setVisible(bool)));
	addAction(fontAction);

	setContextMenuPolicy(Qt::ActionsContextMenu);
}

void MainWindow::writeSettings()
{
	QSettings settings("Software Inc.", "Icon Editor");
	settings.beginGroup("mainWindow");
	settings.setValue("geometry", saveGeometry());
	settings.setValue("state", saveState());
	settings.endGroup();
}

void MainWindow::readSettings()
{
	QSettings settings("Software Inc.", "Icon Editor");
	settings.beginGroup("mainWindow");
	restoreGeometry(settings.value("geometry").toByteArray());
	restoreState(settings.value("state").toByteArray());
	settings.endGroup();
}
