#ifndef MAILCLIENT_H
#define MAILCLIENT_H

#include <QMainWindow>

class QTreeWidgetItem;

QT_BEGIN_NAMESPACE
namespace Ui {
class MailClient;
}
QT_END_NAMESPACE

class MailClient : public QMainWindow
{
	Q_OBJECT

public:
	MailClient(QWidget* parent = nullptr);
	~MailClient();

protected:
	void closeEvent(QCloseEvent* event) override;

private slots:
	void updateMailContent();

private:
	void addMailFolder(const QString& mail);
	void addFolder(QTreeWidgetItem* parent,
				   const QIcon& icon,
				   const QString& name);

	void receiveMails();
	void addMailMessage(const QString& subject,
						const QString& date,
						const QString& sender,
						const QStringList& receivers,
						const QString& content);

	void readSettings();
	void writeSettings();

	void setMailContent(const QString& subject,
						const QString& date,
						const QString& from,
						const QStringList& to,
						const QString& content);

private:
	Ui::MailClient* ui;
};
#endif // MAILCLIENT_H
