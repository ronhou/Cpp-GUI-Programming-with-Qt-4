#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Editor;
class QAction;
class QActionGroup;
class QMdiArea;
class QMenu;
class QToolBar;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

protected:
	void closeEvent(QCloseEvent* event) override;

private slots:
	void newFile();
	void open();
	void save();
	void saveAs();
	void cut();
	void copy();
	void paste();
	void about();
	void updateActions();
	void loadFiles();

private:
	void createActions();
	void createMenus();
	void createToolBars();
	void createStatusBar();

	void addEditor(Editor* editor);
	void openFile(const QString& fileName);
	Editor* activeEditor();

private:
	QMdiArea* m_mdiArea;
	// QMenu* m_fileMenu;
	// QMenu* m_editMenu;
	QMenu* m_windowMenu;
	// QMenu* m_helpMenu;
	// QToolBar* m_fileToolBar;
	// QToolBar* m_editToolBar;
	QAction* m_newAction;
	QAction* m_openAction;
	QAction* m_saveAction;
	QAction* m_saveAsAction;
	QAction* m_exitAction;
	QAction* m_cutAction;
	QAction* m_copyAction;
	QAction* m_pasteAction;
	QAction* m_closeAction;
	QAction* m_closeAllAction;
	QAction* m_tileAction;
	QAction* m_cascadeAction;
	QAction* m_nextAction;
	QAction* m_previousAction;
	QAction* m_separatorAction;
	QAction* m_aboutAction;
	QAction* m_aboutQtAction;
	QActionGroup* m_windowActionGroup;
};
#endif // MAINWINDOW_H
