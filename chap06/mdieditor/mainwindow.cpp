#include "mainwindow.h"
#include "editor.h"

#include <QAction>
#include <QActionGroup>
#include <QApplication>
#include <QCloseEvent>
#include <QLabel>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QTimer>
#include <QToolBar>

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	m_mdiArea = new QMdiArea();
	setCentralWidget(m_mdiArea);
	connect(m_mdiArea,
			SIGNAL(subWindowActivated(QMdiSubWindow*)),
			this,
			SLOT(updateActions()));

	createActions();
	createMenus();
	createToolBars();
	createStatusBar();

	setWindowIcon(QIcon(":/images/icon.png"));
	setWindowTitle(tr("MDI Editor"));
	QTimer::singleShot(0, this, SLOT(loadFiles()));
}

MainWindow::~MainWindow() {}

void MainWindow::closeEvent(QCloseEvent* event)
{
	m_mdiArea->closeAllSubWindows();
	if (!m_mdiArea->subWindowList().empty()) {
		event->ignore();
	} else {
		event->accept();
	}
}

void MainWindow::createActions()
{
	m_newAction = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
	m_newAction->setShortcut(QKeySequence::New);
	m_newAction->setStatusTip(tr("Create a new file"));
	connect(m_newAction, SIGNAL(triggered(bool)), this, SLOT(newFile()));

	m_openAction = new QAction(QIcon(":/images/open.png"), tr("&Open"), this);
	m_openAction->setShortcut(QKeySequence::Open);
	m_openAction->setStatusTip(tr("Open an existing file"));
	connect(m_openAction, SIGNAL(triggered(bool)), this, SLOT(open()));

	m_saveAction = new QAction(QIcon(":/images/save.png"), tr("&New"), this);
	m_saveAction->setShortcut(QKeySequence::Save);
	m_saveAction->setStatusTip(tr("Save the file to disk"));
	connect(m_saveAction, SIGNAL(triggered(bool)), this, SLOT(save()));

	m_saveAsAction = new QAction(tr("Save &As..."), this);
	m_saveAsAction->setShortcut(QKeySequence::SaveAs);
	m_saveAsAction->setStatusTip(tr("Save the file under a new name"));
	connect(m_saveAction, SIGNAL(triggered(bool)), this, SLOT(saveAs()));

	m_exitAction = new QAction(tr("E&xit"), this);
	m_exitAction->setShortcut(QString("Ctrl+Q")); // 快捷键应该不用翻译
	m_exitAction->setStatusTip(tr("Exit the application"));
	connect(m_exitAction, SIGNAL(triggered(bool)), this, SLOT(close()));

	m_cutAction = new QAction(QIcon(":/images/cut.png"), tr("Cu&t"), this);
	m_cutAction->setShortcut(QKeySequence::Cut);
	m_cutAction->setStatusTip(tr("Cut the current selection to the clipboard"));
	connect(m_cutAction, SIGNAL(triggered(bool)), this, SLOT(cut()));

	m_copyAction = new QAction(QIcon(":/images/copy.png"), tr("&Copy"), this);
	m_copyAction->setShortcut(QKeySequence::Copy);
	m_copyAction->setStatusTip(
		tr("Copy the current selection to the clipboard"));
	connect(m_copyAction, SIGNAL(triggered(bool)), this, SLOT(copy()));

	m_pasteAction = new QAction(QIcon(":/images/paste.png"), tr("&Paste"), this);
	m_pasteAction->setShortcut(QKeySequence::Paste);
	m_pasteAction->setStatusTip(
		tr("Paste the clipboard's contents at the cursor position"));
	connect(m_pasteAction, SIGNAL(triggered(bool)), this, SLOT(paste()));

	m_closeAction = new QAction(tr("Cl&ose"), this);
	m_closeAction->setShortcut(QKeySequence::Close);
	m_closeAction->setStatusTip(tr("Close the active window"));
	connect(m_closeAction,
			SIGNAL(triggered(bool)),
			m_mdiArea,
			SLOT(closeActiveSubWindow()));

	m_closeAllAction = new QAction(tr("Close &All"), this);
	m_closeAllAction->setStatusTip(tr("Close all the windows"));
	connect(m_closeAllAction,
			SIGNAL(triggered(bool)),
			m_mdiArea,
			SLOT(closeAllSubWindows()));

	m_tileAction = new QAction(tr("&Tile"), this);
	m_tileAction->setStatusTip(tr("Tile the windows"));
	connect(m_tileAction,
			SIGNAL(triggered(bool)),
			m_mdiArea,
			SLOT(tileSubWindows()));

	m_cascadeAction = new QAction(tr("&Cascade"), this);
	m_cascadeAction->setStatusTip(tr("Cascade the windows"));
	connect(m_cascadeAction,
			SIGNAL(triggered(bool)),
			m_mdiArea,
			SLOT(cascadeSubWindows()));

	m_nextAction = new QAction(tr("Ne&xt"), this);
	m_nextAction->setShortcut(QKeySequence::NextChild);
	m_nextAction->setStatusTip(tr("Move the focus to the next window"));
	connect(m_nextAction,
			SIGNAL(triggered(bool)),
			m_mdiArea,
			SLOT(activateNextSubWindow()));

	m_previousAction = new QAction(tr("Pre&vious"), this);
	m_previousAction->setShortcut(QKeySequence::PreviousChild);
	m_previousAction->setStatusTip(tr("Move the focus to the previous window"));
	connect(m_previousAction,
			SIGNAL(triggered(bool)),
			m_mdiArea,
			SLOT(activatePreviousSubWindow()));

	m_separatorAction = new QAction(this);
	m_separatorAction->setSeparator(true);

	m_aboutAction = new QAction(tr("&About"), this);
	m_aboutAction->setStatusTip(tr("Show the application's About box"));
	connect(m_aboutAction, SIGNAL(triggered(bool)), this, SLOT(about()));

	m_aboutQtAction = new QAction(tr("About &Qt"), this);
	m_aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
	connect(m_aboutQtAction, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));

	m_windowActionGroup = new QActionGroup(this);
}

void MainWindow::createMenus()
{
	QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(m_newAction);
	fileMenu->addAction(m_openAction);
	fileMenu->addAction(m_saveAction);
	fileMenu->addAction(m_saveAsAction);
	fileMenu->addSeparator();
	fileMenu->addAction(m_exitAction);

	QMenu* editMenu = menuBar()->addMenu(tr("&Edit"));
	editMenu->addAction(m_cutAction);
	editMenu->addAction(m_copyAction);
	editMenu->addAction(m_pasteAction);

	m_windowMenu = menuBar()->addMenu(tr("&Window"));
	m_windowMenu->addAction(m_closeAction);
	m_windowMenu->addAction(m_closeAllAction);
	m_windowMenu->addSeparator();
	m_windowMenu->addAction(m_tileAction);
	m_windowMenu->addAction(m_cascadeAction);
	m_windowMenu->addSeparator();
	m_windowMenu->addAction(m_nextAction);
	m_windowMenu->addAction(m_previousAction);
	m_windowMenu->addAction(m_separatorAction);

	menuBar()->addSeparator();

	QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(m_aboutAction);
	helpMenu->addAction(m_aboutQtAction);
}

void MainWindow::createToolBars()
{
	QToolBar* fileToolBar = addToolBar(tr("File"));
	fileToolBar->addAction(m_newAction);
	fileToolBar->addAction(m_openAction);
	fileToolBar->addAction(m_saveAction);

	QToolBar* editToolBar = addToolBar(tr("Edit"));
	editToolBar->addAction(m_cutAction);
	editToolBar->addAction(m_copyAction);
	editToolBar->addAction(m_pasteAction);
}

void MainWindow::createStatusBar()
{
	QLabel* readyLabel = new QLabel(tr(" Ready"));
	statusBar()->addWidget(readyLabel, 1);
}

void MainWindow::updateActions()
{
	bool hasEditor = activeEditor() != nullptr;
	bool hasSelection = activeEditor()
						&& activeEditor()->textCursor().hasSelection();
	m_saveAction->setEnabled(hasEditor);
	m_saveAsAction->setEnabled(hasEditor);
	m_cutAction->setEnabled(hasSelection);
	m_copyAction->setEnabled(hasSelection);
	m_pasteAction->setEnabled(hasEditor);
	m_closeAction->setEnabled(hasEditor);
	m_closeAllAction->setEnabled(hasEditor);
	m_tileAction->setEnabled(hasEditor);
	m_cascadeAction->setEnabled(hasEditor);
	m_nextAction->setEnabled(hasEditor);
	m_previousAction->setEnabled(hasEditor);
	m_separatorAction->setVisible(hasEditor);

	if (activeEditor())
		activeEditor()->windowMenuAction()->setChecked(true);
}

void MainWindow::loadFiles()
{
	QStringList args = QApplication::arguments();
	args.removeFirst();
	if (!args.empty()) {
		foreach (QString arg, args) {
			openFile(arg);
		}
		m_mdiArea->cascadeSubWindows();
	} else {
		newFile();
	}
	m_mdiArea->activateNextSubWindow();
}

void MainWindow::addEditor(Editor* editor)
{
	connect(editor,
			SIGNAL(copyAvailable(bool)),
			m_copyAction,
			SLOT(setEnabled(bool)));
	connect(editor,
			SIGNAL(copyAvailable(bool)),
			m_cutAction,
			SLOT(setEnabled(bool)));

	QMdiSubWindow* subWindow = m_mdiArea->addSubWindow(editor);
	m_windowMenu->addAction(editor->windowMenuAction());
	// QActionGroup对象可以确保每个时刻只能选中Window菜单项中的一项
	m_windowActionGroup->addAction(editor->windowMenuAction());
	subWindow->show();
}

void MainWindow::openFile(const QString& fileName)
{
	Editor* editor = Editor::openFile(fileName, this);
	if (editor)
		addEditor(editor);
}

Editor* MainWindow::activeEditor()
{
	QMdiSubWindow* subWindow = m_mdiArea->activeSubWindow();
	if (subWindow)
		return qobject_cast<Editor*>(subWindow->widget());
	return nullptr;
}

void MainWindow::newFile()
{
	Editor* editor = new Editor;
	editor->newFile();
	addEditor(editor);
}

void MainWindow::open()
{
	Editor* editor = Editor::open(this);
	if (editor)
		addEditor(editor);
}

void MainWindow::save()
{
	if (activeEditor())
		activeEditor()->save();
}

void MainWindow::saveAs()
{
	if (activeEditor())
		activeEditor()->saveAs();
}

void MainWindow::cut()
{
	if (activeEditor())
		activeEditor()->cut();
}

void MainWindow::copy()
{
	if (activeEditor())
		activeEditor()->copy();
}

void MainWindow::paste()
{
	if (activeEditor())
		activeEditor()->paste();
}

void MainWindow::about()
{
	QMessageBox::about(this,
					   tr("About MDI Editor"),
					   tr("<h2>Editor 1.1</h2>"
						  "<p>Copyright &copy; 2007 Software Inc.</p>"
						  "<p>MDI Editor is a small application that "
						  "demonstrates QMdiArea.</p>"));
}
