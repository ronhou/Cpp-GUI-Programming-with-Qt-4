#include "iconeditor.h"

#include <QApplication>
#include <QIcon>
#include <QScrollArea>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	IconEditor* iconEditor = new IconEditor;
	// iconEditor->setWindowTitle(QObject::tr("Icon Editor"));
	// iconEditor->setWindowIcon(QIcon(":/images/mouse.png"));
	iconEditor->setIconImage(QImage(":/images/mouse.png"));
	iconEditor->setPenColor(Qt::red);
	iconEditor->setZoomFactor(10);

	QScrollArea scrollArea;
	scrollArea.setWidget(iconEditor);
	scrollArea.viewport()->setBackgroundRole(QPalette::Dark);
	scrollArea.viewport()->setAutoFillBackground(true);
	// 下面滚动条的策略并没有预想中的生效
	// scrollArea.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	// scrollArea.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	scrollArea.setWindowTitle(QObject::tr("Icon Editor"));
	scrollArea.show();
	return app.exec();
}
