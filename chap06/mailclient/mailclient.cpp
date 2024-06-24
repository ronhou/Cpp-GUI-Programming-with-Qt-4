#include "mailclient.h"
#include "ui_mailclient.h"

#include <QCloseEvent>
#include <QMenuBar>
#include <QSettings>

MailClient::MailClient(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MailClient)
{
	ui->setupUi(this);

	// 本想通过Qt设计师设置菜单栏和状态栏的，但是没有找到入口和方法，于是只好回归使用代码进行设置
	menuBar()->addMenu(tr("&File"));
	menuBar()->addMenu(tr("&Edit"));
	menuBar()->addMenu(tr("&View"));
	menuBar()->addMenu(tr("F&older"));
	menuBar()->addMenu(tr("&Message"));
	menuBar()->addMenu(tr("&Settings"));
	menuBar()->addMenu(tr("&Help"));
	statusBar()->showMessage(tr("No new message on server"));

	addMailFolder(tr("Mail"));

	// 设置前两列列宽自动适应内容
	ui->messageTreeWidget->resizeColumnToContents(0);
	ui->messageTreeWidget->resizeColumnToContents(1);

	// 绑定信号槽：itemSelectionChanged()的时候更新textEdit显示内容
	connect(ui->messageTreeWidget,
			SIGNAL(itemSelectionChanged()),
			this,
			SLOT(updateMailContent()));

	ui->rightSplitter->setStretchFactor(1, 1);
	ui->mainSplitter->setStretchFactor(1, 1);
	setCentralWidget(ui->mainSplitter);
	readSettings();
	receiveMails();
}

MailClient::~MailClient()
{
	delete ui;
}

void MailClient::closeEvent(QCloseEvent* event)
{
	writeSettings();
	event->accept();
}

void MailClient::addMailFolder(const QString& mail)
{
	QTreeWidgetItem* root = new QTreeWidgetItem(ui->foldersTreeWidget);
	root->setText(0, mail);

	QIcon folderIcon = style()->standardIcon(QStyle::SP_DirClosedIcon);
	QIcon trashIcon = style()->standardIcon(QStyle::SP_TrashIcon);
	addFolder(root, folderIcon, tr("Inbox"));
	addFolder(root, folderIcon, tr("Outbox"));
	addFolder(root, folderIcon, tr("Sent"));
	addFolder(root, trashIcon, tr("Trash"));
}

void MailClient::addFolder(QTreeWidgetItem* parent,
						   const QIcon& icon,
						   const QString& name)
{
	QTreeWidgetItem* newItem = new QTreeWidgetItem(parent);
	newItem->setIcon(0, icon);
	newItem->setText(0, name);
}

void MailClient::addMailMessage(const QString& subject,
								const QString& date,
								const QString& sender,
								const QStringList& receivers,
								const QString& content)
{
	QTreeWidgetItem* newItem = new QTreeWidgetItem(ui->messageTreeWidget);
	newItem->setText(0, subject);
	newItem->setText(1, sender);
	newItem->setText(2, date);
	// 数据应该和UI-窗口部件解耦，暂时先设置在item上
	newItem->setData(0, Qt::UserRole, content);
	newItem->setData(1, Qt::UserRole, receivers);

	if (!ui->messageTreeWidget->currentItem())
		ui->messageTreeWidget->setCurrentItem(newItem);
}

void MailClient::readSettings()
{
	QSettings settings("Software Inc.", "Mail Client");

	settings.beginGroup("mainWindow");
	restoreGeometry(settings.value("geometry").toByteArray());
	ui->mainSplitter->restoreState(
		settings.value("mainSplitter").toByteArray());
	ui->rightSplitter->restoreState(
		settings.value("rightSplitter").toByteArray());
	settings.endGroup();
}

void MailClient::writeSettings()
{
	QSettings settings("Software Inc.", "Mail Client");

	settings.beginGroup("mainWindow");
	settings.setValue("geometry", saveGeometry());
	settings.setValue("mainSplitter", ui->mainSplitter->saveState());
	settings.setValue("rightSplitter", ui->rightSplitter->saveState());
	settings.endGroup();
}

void MailClient::updateMailContent()
{
	QList<QTreeWidgetItem*> selectedItems = ui->messageTreeWidget->selectedItems();
	if (selectedItems.isEmpty())
		return;

	const QTreeWidgetItem* firstItem = selectedItems.first();
	setMailContent(firstItem->text(0),
				   firstItem->text(2),
				   firstItem->text(1),
				   firstItem->data(1, Qt::UserRole).toStringList(),
				   firstItem->data(0, Qt::UserRole).toString());
}

void MailClient::receiveMails()
{
	addMailMessage(
		tr("Happy New Year!"),
		tr("2006-12-31"),
		tr("Grace K. <grace@software-inc.com>").toHtmlEscaped(),
		QStringList({tr("ALL <all@software-inc.com>").toHtmlEscaped()}),
		QString::fromUtf8(
			"<br>I want to seize this occasion to thank everybody for "
			"the year that has gone, and want to wish you the best for "
			"next year. It has been a pleasure to work with you all on "
			"the Hawk project, and I'm sure we'll get concrete results "
			"shortly.<br><br>Happy New Year!<br>--Grace"));
	addMailMessage(tr("Radically new concept!"),
				   tr("2006-12-22"),
				   tr("Grace K. <grace@software-inc.com>").toHtmlEscaped(),
				   QStringList(
					   {tr("ALL <all@software-inc.com>").toHtmlEscaped()}),
				   QString::fromUtf8("<br>This is radically new concept! Next "
									 "is the content of the new concept."));
	addMailMessage(tr("Accounts"),
				   tr("2006-12-31"),
				   tr("pascale@nospam.com"),
				   QStringList({tr("Ronald <a@qq.com>").toHtmlEscaped()}),
				   QString::fromUtf8("Here is you new account with which's "
									 "password is youer ID number"));
	addMailMessage(tr("Expenses"),
				   tr("2006-12-25"),
				   tr("Joe Bloggs <joe@bloggs.com>").toHtmlEscaped(),
				   QStringList({tr("Ronald <a@qq.com>").toHtmlEscaped(),
								tr("B <b@qq.com>").toHtmlEscaped()}),
				   QString::fromUtf8(
					   "This is the content of the email \"Expenses\""));
	addMailMessage(tr("Re: Expenses"),
				   tr("2007-01-02"),
				   tr("Andy <andy@nospam.com>").toHtmlEscaped(),
				   QStringList({tr("Ronald <a@qq.com>").toHtmlEscaped()}),
				   QString::fromUtf8(
					   "This is the content of the email \"Re: Expenses\""));
	addMailMessage(tr("Re: Accounts"),
				   tr("2007-01-03"),
				   tr("Joe Bloggs <joe@bloggs.com>").toHtmlEscaped(),
				   QStringList({tr("Ronald <a@qq.com>").toHtmlEscaped()}),
				   QString::fromUtf8(
					   "This is the content of the email \"Re: Accounts\""));
	addMailMessage(tr("Re: Accounts"),
				   tr("2007-01-03"),
				   tr("Andy <andy@nospam.com>").toHtmlEscaped(),
				   QStringList({tr("Ronald <a@qq.com>").toHtmlEscaped()}),
				   QString::fromUtf8(
					   "This is the content of the email \"Re:Re: Accounts\""));

	// 设置前两列列宽自动适应内容
	ui->messageTreeWidget->resizeColumnToContents(0);
	ui->messageTreeWidget->resizeColumnToContents(1);
}

void MailClient::setMailContent(const QString& subject,
								const QString& date,
								const QString& from,
								const QStringList& to,
								const QString& content)
{
	const QString mailHeader = QString("<table bolder=0>"
									   "<tr><td align=right><b>%1</b>"
									   "<td><p>%2"
									   "<tr><td align=right><b>%3</b>"
									   "<td><p>%4"
									   "<tr><td align=right><b>%5</b>"
									   "<td><p>%6"
									   "<tr><td align=right><b>%7</b>"
									   "<td>%8"
									   "</table>")
								   .arg(tr("Subject:"),
										subject,
										tr("Date:"),
										date,
										tr("From:"),
										from,
										tr("To:"),
										to.join(tr(";")));
	ui->textEdit->setHtml(mailHeader + content);
}
