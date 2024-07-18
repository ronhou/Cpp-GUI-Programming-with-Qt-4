#include "ticker.h"

#include <QApplication>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	Ticker ticker;
	ticker.setText(QObject::tr("How long it lasted was impossible to say ++ "));
	ticker.show();
	return app.exec();
}
