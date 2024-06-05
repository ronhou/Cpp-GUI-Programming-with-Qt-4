#ifndef PREFERENCEDIALOG_H
#define PREFERENCEDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class PreferenceDialog;
}
QT_END_NAMESPACE

class PreferenceDialog : public QDialog
{
	Q_OBJECT

public:
	PreferenceDialog(QWidget* parent = nullptr);
	~PreferenceDialog();

private:
	Ui::PreferenceDialog* ui;
};
#endif // PREFERENCEDIALOG_H
