#ifndef HEXSPINBOX_H
#define HEXSPINBOX_H

#include <QObject>
#include <QSpinBox>

class HexSpinBox : public QSpinBox
{
	Q_OBJECT
public:
	HexSpinBox(QWidget* parent = nullptr);

protected:
	QValidator::State validate(QString& input, int& pos) const;
	int valueFromText(const QString& text) const override;
	QString textFromValue(int val) const override;

private:
	QRegExpValidator* validator;
};

#endif // HEXSPINBOX_H
