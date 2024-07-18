#include "ticker.h"

#include <QPainter>
#include <QTimerEvent>

Ticker::Ticker(QWidget* parent)
	: QWidget(parent)
{
	m_offset = 0;
	m_nTimerId = 0;
}

Ticker::~Ticker() {}

QSize Ticker::sizeHint() const
{
	return fontMetrics().size(0, text());
}

void Ticker::setText(const QString& text)
{
	m_text = text;
	update();
	updateGeometry();
}

void Ticker::paintEvent(QPaintEvent* /*event*/)
{
	int textWidth = fontMetrics().horizontalAdvance(text());
	if (textWidth < 1)
		return;

	QPainter painter(this);

	int x = -m_offset;
	while (x < width()) {
		painter.drawText(x,
						 0,
						 textWidth,
						 height(),
						 Qt::AlignLeft | Qt::AlignVCenter,
						 text());
		x += textWidth;
	}
}

void Ticker::showEvent(QShowEvent* /*event*/)
{
	m_nTimerId = startTimer(30);
}

void Ticker::hideEvent(QHideEvent* /*event*/)
{
	killTimer(m_nTimerId);
	m_nTimerId = 0;
}

void Ticker::timerEvent(QTimerEvent* event)
{
	if (event->timerId() == m_nTimerId) {
		++m_offset;
		if (m_offset >= fontMetrics().horizontalAdvance(text()))
			m_offset = 0;
		scroll(-1, 0);
	} else {
		QWidget::timerEvent(event);
	}
}
