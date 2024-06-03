#ifndef FINDFILEDIALOG_H
#define FINDFILEDIALOG_H

#include <QDialog>

class QLabel;
class QLineEdit;
class QCheckBox;
class QTableWidget;
class QPushButton;

class FindFileDialog : public QDialog
{
	Q_OBJECT

public:
	FindFileDialog(QWidget* parent = nullptr);
	~FindFileDialog();

protected:
	void resizeEvent(QResizeEvent* event) override;

private:
	QLabel* namedLabel;
	QLabel* lookInLabel;
	QLineEdit* namedLineEdit;
	QLineEdit* lookInLineEdit;
	QCheckBox* subfoldersCheckBox;
	QTableWidget* tableWidget;
	QLabel* messageLabel;
	QPushButton* findButton;
	QPushButton* stopButton;
	QPushButton* closeButton;
	QPushButton* helpButton;
};
#endif // FINDFILEDIALOG_H
