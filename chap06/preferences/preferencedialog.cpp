#include "preferencedialog.h"
#include "ui_preferencedialog.h"

PreferenceDialog::PreferenceDialog(QWidget* parent)
	: QDialog(parent)
	, ui(new Ui::PreferenceDialog)
{
	ui->setupUi(this);
}

PreferenceDialog::~PreferenceDialog()
{
	delete ui;
}
