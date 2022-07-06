#include "widget.h"

#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>
#include <QPair>

#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui_(std::make_unique<Ui::Widget>())
{
    ui_->setupUi(this);

    auto spinBox = new QSpinBox;
    auto slider = new QSlider(Qt::Horizontal);

    QPair<int, int> range(0, 130);
    spinBox->setRange(range.first, range.second);
    slider->setRange(range.first, range.second);

    QObject::connect(spinBox, qOverload<int>(&QSpinBox::valueChanged), slider, &QSlider::setValue);
    QObject::connect(slider, qOverload<int>(&QSlider::valueChanged), spinBox, &QSpinBox::setValue);

    spinBox->setValue(35);

    auto layout = new QHBoxLayout;
    layout->addWidget(spinBox);
    layout->addWidget(slider);

    setLayout(layout);
}

Widget::~Widget() = default;
