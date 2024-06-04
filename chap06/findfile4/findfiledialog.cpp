#include "findfiledialog.h"
#include "ui_findfiledialog.h"

FindFileDialog::FindFileDialog(QWidget* parent)
	: QDialog(parent)
	, ui(new Ui::FindFileDialog)
{
	ui->setupUi(this);
}

FindFileDialog::~FindFileDialog()
{
	delete ui;
}
