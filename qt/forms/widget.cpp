#include "widget.h"

#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui_(std::make_unique<Ui::Widget>())
{
    ui_->setupUi(this);
}

Widget::~Widget() = default;
