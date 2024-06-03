#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QResizeEvent>
#include <QTableWidget>

#include "findfiledialog.h"

FindFileDialog::FindFileDialog(QWidget* parent)
	: QDialog(parent)
{
	namedLabel = new QLabel(tr("&Named:"), this);
	namedLineEdit = new QLineEdit(this);
	namedLabel->setBuddy(namedLineEdit);

	lookInLabel = new QLabel(tr("&Look in:"), this);
	lookInLineEdit = new QLineEdit(this);
	lookInLabel->setBuddy(lookInLineEdit);

	subfoldersCheckBox = new QCheckBox(tr("&Include subfolders"), this);

	QStringList labels;
	labels << tr("Name") << tr("In Folder") << tr("Size") << tr("Modified");

	tableWidget = new QTableWidget(this);
	tableWidget->setColumnCount(labels.count());
	tableWidget->setHorizontalHeaderLabels(labels);

	messageLabel = new QLabel(tr("0 files found"), this);
	messageLabel->setFrameShape(QLabel::Panel);
	messageLabel->setFrameShadow(QLabel::Sunken);

	findButton = new QPushButton(tr("&Find"), this);
	stopButton = new QPushButton(tr("&Stop"), this);
	closeButton = new QPushButton(tr("&Close"), this);
	helpButton = new QPushButton(tr("&Help"), this);

	connect(closeButton, SIGNAL(clicked(bool)), this, SLOT(close()));

	setWindowTitle(tr("Find Files or Folders"));
	setMinimumSize(265, 190);
	resize(365, 240);
}

FindFileDialog::~FindFileDialog() {}

void FindFileDialog::resizeEvent(QResizeEvent* /*event*/)
{
	int extraWidth = width() - minimumWidth();
	int extraHeight = height() - minimumHeight();

	namedLabel->setGeometry(9, 9, 50, 25);
	namedLineEdit->setGeometry(65, 9, 100 + extraWidth, 25);
	lookInLabel->setGeometry(9, 40, 50, 25);
	lookInLineEdit->setGeometry(65, 40, 100 + extraWidth, 25);
	subfoldersCheckBox->setGeometry(9, 71, 156 + extraWidth, 25);
	tableWidget->setGeometry(9, 102, 156 + extraWidth, 50 + extraHeight);
	messageLabel->setGeometry(9, 158 + extraHeight, 156 + extraWidth, 25);

	findButton->setGeometry(171 + extraWidth, 9, 85, 32);
	stopButton->setGeometry(171 + extraWidth, 47, 85, 32);
	closeButton->setGeometry(171 + extraWidth, 85, 85, 32);
	helpButton->setGeometry(171 + extraWidth, 151 + extraHeight, 85, 32);
}
