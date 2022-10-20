#include "login_main_dlg.h"

#include <memory>

#include <QMouseEvent>

#include "ui_login_main_dlg.h"

namespace hestina {
namespace client {
namespace ui {

login_main_dlg::login_main_dlg(QWidget* parent)
    : QDialog(parent), ui_(std::make_unique<Ui::login_main_dlg>()) {
    ui_->setupUi(this);

    // setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint);
    setWindowFlag(Qt::FramelessWindowHint);

    ui_->password->setEchoMode(QLineEdit::EchoMode::Password);
    ui_->logo_text->setPixmap(
        QPixmap(":/login/logo_text.png")
            .scaled(ui_->logo_text->size(), Qt::KeepAspectRatio,
                Qt::SmoothTransformation));
}

login_main_dlg::~login_main_dlg() = default;

void login_main_dlg::mousePressEvent(QMouseEvent* event) {
    is_pressed_ = true;
    pre_move_point_ = event->globalPos();
}

void login_main_dlg::mouseReleaseEvent(QMouseEvent* event) {
    is_pressed_ = false;
}

void login_main_dlg::mouseMoveEvent(QMouseEvent* event) {
    auto now_move_point = event->globalPos();
    move(now_move_point - pre_move_point_ + pos());
    pre_move_point_ = now_move_point;
}

}  // namespace ui
}  // namespace client
}  // namespace hestina
