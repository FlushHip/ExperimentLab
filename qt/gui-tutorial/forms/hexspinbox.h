#pragma once

#include <memory>

#include <QSpinBox>

class QRegExpValidator;

class HexSpinBox : public QSpinBox
{
    Q_OBJECT
public:
    HexSpinBox(QWidget *parent = Q_NULLPTR);
    ~HexSpinBox() override;

protected:
    QValidator::State validate(QString &input, int &pos) const override;
    int valueFromText(const QString &text) const override;
    QString textFromValue(int val) const override;

private:
    std::unique_ptr<QRegExpValidator> validator_;
};
