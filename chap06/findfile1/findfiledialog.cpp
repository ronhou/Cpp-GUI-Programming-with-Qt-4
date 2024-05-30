#include "findfiledialog.h"

#include <QCheckBox>
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

	setWidgetsGeometry();
	setWindowTitle(tr("Find Files or Folders"));
}

FindFileDialog::~FindFileDialog() {}

// 由于历史原因，
// QRect::right() 返回的是 QRect::left() + QRect::width() - 1
// QRectF 就没有这个问题
int getQRectRight(const QRect& rect)
{
	return rect.left() + rect.width();
}

// 由于历史原因，
// QRect::bottom() 返回的是 QRect::top() + QRect::height() -1
// QRectF 就没有这个问题
int getQRectBottom(const QRect& rect)
{
	return rect.top() + rect.height();
}

void FindFileDialog::setWidgetsGeometry()
{
	const int horiMargin = 9, vertMargin = 9;
	const int labelLeft = horiMargin, labelTop = vertMargin;
	const int labelWidth = 50, labelHeight = 25;
	namedLabel->setGeometry(labelLeft, labelTop, labelWidth, labelHeight);

	const int horiPadding = 6, vertPadding = 6, lineEditWidth = 200;
	namedLineEdit->setGeometry(getQRectRight(namedLabel->geometry()) + horiPadding,
							   namedLabel->geometry().top(),
							   lineEditWidth,
							   namedLabel->geometry().height());
	lookInLabel->setGeometry(namedLabel->geometry().left(),
							 getQRectBottom(namedLabel->geometry()) + vertPadding,
							 labelWidth,
							 labelHeight);
	lookInLineEdit->setGeometry(getQRectRight(lookInLabel->geometry()) + horiPadding,
								lookInLabel->geometry().top(),
								lineEditWidth,
								lookInLabel->geometry().height());

	const int leftWidgetWidth = labelWidth + lineEditWidth + horiPadding;
	subfoldersCheckBox->setGeometry(namedLabel->geometry().left(),
									getQRectBottom(lookInLabel->geometry()) + vertPadding,
									leftWidgetWidth,
									labelHeight);

	const int tableWidgetHeight = 100;
	tableWidget->setGeometry(namedLabel->geometry().left(),
							 getQRectBottom(subfoldersCheckBox->geometry()) + vertPadding,
							 leftWidgetWidth,
							 tableWidgetHeight);
	messageLabel->setGeometry(namedLabel->geometry().left(),
							  getQRectBottom(tableWidget->geometry()) + vertPadding,
							  leftWidgetWidth,
							  labelHeight);

	const int buttonLeft = horiMargin + leftWidgetWidth + horiPadding;
	const int buttonWidth = 85, buttonHieght = 32;
	findButton->setGeometry(buttonLeft,
							namedLabel->geometry().top(),
							buttonWidth,
							buttonHieght);
	stopButton->setGeometry(buttonLeft,
							getQRectBottom(findButton->geometry()) + vertPadding,
							buttonWidth,
							buttonHieght);
	closeButton->setGeometry(buttonLeft,
							 getQRectBottom(stopButton->geometry()) + vertPadding,
							 buttonWidth,
							 buttonHieght);

	const int dialogHeight = getQRectBottom(messageLabel->geometry())
							 + vertMargin;
	helpButton->setGeometry(buttonLeft,
							dialogHeight - vertMargin - buttonHieght,
							buttonWidth,
							buttonHieght);

	const int dialogWidth = horiMargin + leftWidgetWidth + horiPadding + buttonWidth + horiMargin;
	setFixedSize(dialogWidth, dialogHeight);
}
