#ifndef GOTOCELLDIALOG_H
#define GOTOCELLDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class GoToCellDialog;
}
QT_END_NAMESPACE

class GoToCellDialog : public QDialog
{
    Q_OBJECT

public:
    GoToCellDialog(QWidget *parent = nullptr);
    ~GoToCellDialog();

private slots:
    void on_lineEdit_textChanged();

public:
    Ui::GoToCellDialog *ui;
};
#endif // GOTOCELLDIALOG_H
