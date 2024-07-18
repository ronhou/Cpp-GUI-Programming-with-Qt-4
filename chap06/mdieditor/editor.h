#ifndef EDITOR_H
#define EDITOR_H

#include <QTextEdit>

class QAction;

class Editor : public QTextEdit
{
	Q_OBJECT
public:
	Editor(QWidget* parent = nullptr);
	~Editor();

public:
	QSize sizeHint() const override;

	static Editor* open(QWidget* parent = nullptr);
	static Editor* openFile(const QString& fileName, QWidget* parent = nullptr);

	void newFile();
	bool save();
	bool saveAs();
	QAction* windowMenuAction() const { return m_action; }

protected:
	void closeEvent(QCloseEvent* event) override;

private slots:
	void documentWasModified();

private:
	bool okToContinue();
	bool saveFile(const QString& fileName);
	void setCurrentFile(const QString& fileName);
	bool readFile(const QString& fileName);
	bool writeFile(const QString& fileName);
	QString strippedName(const QString& fileName);

private:
	QString m_curFile;
	bool m_isUntitled;
	QAction* m_action;
};

#endif // EDITOR_H
