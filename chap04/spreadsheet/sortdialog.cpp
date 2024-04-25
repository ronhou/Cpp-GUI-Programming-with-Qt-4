#include "sortdialog.h"
#include "ui_sortdialog.h"

SortDialog::SortDialog(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::SortDialog)
{
	ui->setupUi(this);
	ui->secondaryGroupBox->hide();
	ui->tertiaryGroupBox->hide();
	// 亦可通过ui文件对layout进行设置
	// 设置布局为不可改变尺寸大小，这样会使用户不能修改这个对话框窗体的大小。
	// layout()->setSizeConstraint(QLayout::SetFixedSize);

	setColumnRange('A', 'Z');
}

SortDialog::~SortDialog()
{
	delete ui;
}

void SortDialog::setColumnRange(QChar first, QChar last)
{
	ui->primaryColumnCombo->clear();
	ui->secondaryColumnCombo->clear();
	ui->tertiaryColumnCombo->clear();

	// 至少需要一个主键
	// ui->primaryColumnCombo->addItem(tr("None"));
	ui->secondaryColumnCombo->addItem(tr("None"));
	ui->tertiaryColumnCombo->addItem(tr("None"));
	// 主键组合框没有None默认选项时，宽度会偏窄。
	// 为了避免这种不一致性，需要把主键组合框的最小大小设置成第二键组合框的理想大小。
	ui->primaryColumnCombo->setMinimumSize(ui->secondaryColumnCombo->sizeHint());

	for (QChar ch = first; ch <= last; ch = ch.unicode() + 1)
	{
		ui->primaryColumnCombo->addItem(QString(ch));
		ui->secondaryColumnCombo->addItem(QString(ch));
		ui->tertiaryColumnCombo->addItem(QString(ch));
	}
}
