#include "iconeditor.h"

#include <QApplication>
#include <QIcon>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	IconEditor iconEditor;
	iconEditor.setWindowTitle(QObject::tr("Icon Editor"));
	iconEditor.setWindowIcon(QIcon(":/images/mouse.png"));
	iconEditor.setIconImage(QImage(":/images/mouse.png"));
	iconEditor.setPenColor(Qt::red);
	iconEditor.setZoomFactor(10);
	iconEditor.show();
	return app.exec();
}
