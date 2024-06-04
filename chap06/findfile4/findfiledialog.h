#ifndef FINDFILEDIALOG_H
#define FINDFILEDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class FindFileDialog;
}
QT_END_NAMESPACE

class FindFileDialog : public QDialog
{
	Q_OBJECT

public:
	FindFileDialog(QWidget* parent = nullptr);
	~FindFileDialog();

private:
	Ui::FindFileDialog* ui;
};
#endif // FINDFILEDIALOG_H
