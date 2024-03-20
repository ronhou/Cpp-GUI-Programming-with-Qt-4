#include <QPushButton>
#include <QRegExp>
#include <QRegExpValidator>
#include "gotocelldialog.h"
#include "ui_gotocelldialog.h"

GoToCellDialog::GoToCellDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GoToCellDialog)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    QRegExp regExp("[A-Za-z][1-9][0-9]{0,2}");
    ui->lineEdit->setValidator(new QRegExpValidator(regExp, this));

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

GoToCellDialog::~GoToCellDialog()
{
    delete ui;
}

void GoToCellDialog::on_lineEdit_textChanged()
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(
        ui->lineEdit->hasAcceptableInput());
}
