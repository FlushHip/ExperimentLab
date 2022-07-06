#pragma once

#include <QWidget>

namespace Ui
{
class Widget;
} // namespace Ui

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = Q_NULLPTR);
    ~Widget() override;

private:
    std::unique_ptr<Ui::Widget> ui_;
};
