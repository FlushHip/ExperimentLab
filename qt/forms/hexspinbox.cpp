#include "hexspinbox.h"

#include <QRegExpValidator>

HexSpinBox::HexSpinBox(QWidget *parent)
    : QSpinBox(parent)
    , validator_(std::make_unique<QRegExpValidator>(QRegExp("[0-9A-Fa-f]{1,8}")))
{
    setRange(0, 255);
}

HexSpinBox::~HexSpinBox() = default;

QValidator::State HexSpinBox::validate(QString &input, int &pos) const
{
    return validator_->validate(input, pos);
}

QString HexSpinBox::textFromValue(int val) const
{
    return QString::number(val, 16).toUpper();
}

int HexSpinBox::valueFromText(const QString &text) const
{
    bool ok = false;
    return text.toInt(&ok, 16);
}
