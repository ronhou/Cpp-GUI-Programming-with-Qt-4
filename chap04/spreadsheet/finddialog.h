#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>

class QLabel;
class QLineEdit;
class QCheckBox;
class QPushButton;

class FindDialog : public QDialog
{
	Q_OBJECT

public:
	FindDialog(QWidget *parent = nullptr);
	~FindDialog();

signals:
	void findNext(const QString &str, Qt::CaseSensitivity cs);
	void findPrev(const QString &str, Qt::CaseSensitivity cs);

private slots:
	void findClicked();
	void enableFindButton(const QString &text);

private:
	QLabel *label;
	QLineEdit *lineEdit;
	QCheckBox *caseCheckBox;
	QCheckBox *backwardCheckBox;
	QPushButton *findButton;
	QPushButton *closeButton;
};
#endif // FINDDIALOG_H
