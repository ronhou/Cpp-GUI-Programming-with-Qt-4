#include "widget.h"

#include <QPaintEvent>
#include <QPainter>

Widget::Widget(QWidget* parent)
	: QWidget(parent)
{}

Widget::~Widget() {}

void Widget::paintEvent(QPaintEvent* /*event*/)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setPen(
		QPen(Qt::black, 15, Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin));

	QLinearGradient lineGradient(80, 80, 400, 240);
	lineGradient.setColorAt(0.0, Qt::white);
	lineGradient.setColorAt(0.25, Qt::red);
	lineGradient.setColorAt(0.5, Qt::green);
	lineGradient.setColorAt(0.75, Qt::yellow);
	lineGradient.setColorAt(1.0, Qt::black);

	painter.setBrush(QBrush(lineGradient));
	painter.drawPie(80, 80, 400, 240, 60 * 16, 270 * 16);

	QPainterPath path;
	path.moveTo(80, 560);
	path.cubicTo(200, 320, 320, 320, 480, 560);

	painter.setPen(QPen(Qt::black, 8));
	painter.drawPath(path);
}
