#include "findfiledialog.h"

#include <QApplication>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	FindFileDialog dialog;
	dialog.show();
	return app.exec();
}
