#include "findfiledialog.h"

#include <QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	FindFileDialog w;
	w.show();
	return a.exec();
}
