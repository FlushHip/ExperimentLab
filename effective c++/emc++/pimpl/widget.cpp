#include "widget.h"

#include <string>

struct Widget::Impl {
    std::string name;
};

Widget::Widget() : impl_(std::make_unique<Impl>()) {}
Widget::~Widget() = default;
