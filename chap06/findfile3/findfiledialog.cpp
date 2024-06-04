#include "findfiledialog.h"

#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>

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

	setLayouts();
	setWindowTitle(tr("Find Files or Folders"));
}

FindFileDialog::~FindFileDialog() {}

void FindFileDialog::setLayouts()
{
	QGridLayout* leftLayout = new QGridLayout;
	leftLayout->addWidget(namedLabel, 0, 0);
	leftLayout->addWidget(namedLineEdit, 0, 1);
	leftLayout->addWidget(lookInLabel, 1, 0);
	leftLayout->addWidget(lookInLineEdit, 1, 1);
	leftLayout->addWidget(subfoldersCheckBox, 2, 0, 1, 2);
	leftLayout->addWidget(tableWidget, 3, 0, 1, 2);
	leftLayout->addWidget(messageLabel, 4, 0, 1, 2);

	QVBoxLayout* rightLayout = new QVBoxLayout;
	rightLayout->addWidget(findButton);
	rightLayout->addWidget(stopButton);
	rightLayout->addWidget(closeButton);
	rightLayout->addStretch();
	rightLayout->addWidget(helpButton);

	QHBoxLayout* mainLayout = new QHBoxLayout;
	mainLayout->addLayout(leftLayout);
	mainLayout->addLayout(rightLayout);

	setLayout(mainLayout);
}
