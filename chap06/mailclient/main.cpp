#include "mailclient.h"

#include <QApplication>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	MailClient client;
	client.show();
	return app.exec();
}
