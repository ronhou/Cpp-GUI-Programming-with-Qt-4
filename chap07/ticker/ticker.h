#ifndef TICKER_H
#define TICKER_H

#include <QWidget>

class Ticker : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(QString text READ text WRITE setText)

public:
	Ticker(QWidget* parent = nullptr);
	~Ticker();

	QSize sizeHint() const override;

	QString text() const { return m_text; }
	void setText(const QString& text);

protected:
	void paintEvent(QPaintEvent* event) override;
	void showEvent(QShowEvent* event) override;
	void hideEvent(QHideEvent* event) override;
	void timerEvent(QTimerEvent* event) override;

private:
	QString m_text;
	int m_offset;
	int m_nTimerId;
};
#endif // TICKER_H
