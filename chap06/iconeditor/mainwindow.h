#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class IconEditor;
class QScrollArea;
class QAction;
class QToolBar;
class QDockWidget;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private:
	void createActions();
	void createMenus();
	void createToolBars();
	void addShapesDocWidget();
	void createContextMenu();
	void writeSettings();
	void readSettings();

private:
	IconEditor* m_iconEditor;
	QScrollArea* m_scrollArea;

	QAction* m_newAction;
	QAction* m_openAction;
	QAction* m_saveAction;
	QAction* m_printAction;
	QAction* m_cutAction;
	QAction* m_copyAction;
	QAction* m_pasteAction;

	QToolBar* m_fileToolBar;
	QToolBar* m_editToolBar;
	QToolBar* m_fontToolBar;

	QDockWidget* m_shapesDocWidget;
};

#endif // MAINWINDOW_H
