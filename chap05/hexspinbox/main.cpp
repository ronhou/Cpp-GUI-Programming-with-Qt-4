#include "hexspinbox.h"

#include <QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	HexSpinBox spinBox;
	spinBox.setWindowTitle(QObject::tr("Hex Spin Box"));
	spinBox.show();
	return a.exec();
}
