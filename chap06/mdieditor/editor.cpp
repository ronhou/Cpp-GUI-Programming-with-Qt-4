#include "editor.h"

#include <QAction>
#include <QApplication>
#include <QCloseEvent>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QTextStream>

Editor::Editor(QWidget* parent)
	: QTextEdit(parent)
{
	m_action = new QAction(this);
	m_action->setCheckable(true);
	connect(m_action, SIGNAL(triggered(bool)), this, SLOT(show()));
	connect(m_action, SIGNAL(triggered(bool)), this, SLOT(setFocus()));

	m_isUntitled = true;

	connect(document(),
			SIGNAL(contentsChanged()),
			this,
			SLOT(documentWasModified()));

	setWindowIcon(QIcon(":/images/document.png"));
	setWindowTitle("[*]");
	setAttribute(Qt::WA_DeleteOnClose);
}

Editor::~Editor() {}

QSize Editor::sizeHint() const
{
	return QSize(72 * fontMetrics().horizontalAdvance('M'),
				 25 * fontMetrics().lineSpacing());
}

Editor* Editor::open(QWidget* parent)
{
	QString fileName = QFileDialog::getOpenFileName(parent, tr("Open"), ".");
	if (fileName.isEmpty())
		return nullptr;
	return openFile(fileName, parent);
}

Editor* Editor::openFile(const QString& fileName, QWidget* parent)
{
	Editor* editor = new Editor(parent);
	if (editor->readFile(fileName)) {
		editor->setCurrentFile(fileName);
	} else {
		delete editor;
		editor = nullptr;
	}
	return editor;
}

void Editor::newFile()
{
	static int documentNumber = 1;

	QString curFile = tr("document%1.txt").arg(documentNumber);
	setWindowTitle(curFile + "[*]");
	m_action->setText(curFile);
	m_isUntitled = true;
	++documentNumber;
}

bool Editor::save()
{
	if (m_isUntitled) {
		return saveAs();
	} else {
		return saveFile(m_curFile);
	}
}

bool Editor::saveAs()
{
	QString fileName = QFileDialog::getSaveFileName(this,
													tr("Save As"),
													m_curFile);
	if (fileName.isEmpty())
		return false;
	return saveFile(fileName);
}

void Editor::closeEvent(QCloseEvent* event)
{
	if (okToContinue()) {
		event->accept();
	} else {
		event->ignore();
	}
}

void Editor::documentWasModified()
{
	setWindowModified(true);
}

bool Editor::okToContinue()
{
	if (document()->isModified()) {
		int r = QMessageBox::warning(
			this,
			tr("Editor"),
			tr("File %1 has been modified.\n Do you want to save your changes?")
				.arg(strippedName(m_curFile)),
			QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
		if (r == QMessageBox::Yes) {
			return save();
		} else if (r == QMessageBox::Cancel) {
			return false;
		}
	}
	return true;
}

bool Editor::saveFile(const QString& fileName)
{
	if (writeFile(fileName)) {
		setCurrentFile(fileName);
		return true;
	}
	return false;
}

void Editor::setCurrentFile(const QString& fileName)
{
	m_curFile = fileName;
	m_isUntitled = false;
	m_action->setText(strippedName(m_curFile));
	setWindowTitle(strippedName(m_curFile) + "[*]");
	document()->setModified(false);
	setWindowModified(false);
}

bool Editor::readFile(const QString& fileName)
{
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QMessageBox::warning(this,
							 tr("Editor"),
							 tr("Cannot read file %1:\n%2.")
								 .arg(file.fileName(), file.errorString()));
		return false;
	}

	QTextStream in(&file);
	QApplication::setOverrideCursor(Qt::WaitCursor);
	setPlainText(in.readAll());
	QApplication::restoreOverrideCursor();
	return true;
}

bool Editor::writeFile(const QString& fileName)
{
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		QMessageBox::warning(this,
							 tr("Editor"),
							 tr("Cannot write file %1:\n%2.")
								 .arg(file.fileName(), file.errorString()));
		return false;
	}

	QTextStream out(&file);
	QApplication::setOverrideCursor(Qt::WaitCursor);
	out << toPlainText();
	QApplication::restoreOverrideCursor();
	return true;
}

QString Editor::strippedName(const QString& fileName)
{
	return QFileInfo(fileName).fileName();
}
