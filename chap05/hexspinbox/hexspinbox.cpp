#include "hexspinbox.h"

HexSpinBox::HexSpinBox(QWidget* parent)
	: QSpinBox(parent)
{
	setRange(0, 0xFF);
	validator = new QRegExpValidator(QRegExp("[0-9A-Fa-f]{1,8}"), this);
}

QValidator::State HexSpinBox::validate(QString& input, int& pos) const
{
	return validator->validate(input, pos);
}

int HexSpinBox::valueFromText(const QString& text) const
{
	bool ok = false;
	return text.toInt(&ok, 16);
}

QString HexSpinBox::textFromValue(int val) const
{
	return QString::number(val, 16).toUpper();
}
