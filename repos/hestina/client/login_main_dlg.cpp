#include "login_main_dlg.h"
#include <qdebug.h>
#include <qpushbutton.h>
#include <qregexp.h>
#include <qvalidator.h>

#include <iostream>
#include <memory>

#include <QDebug>
#include <QMouseEvent>
#include <QRegExpValidator>

#include "client/login_main_dlg.h"
#include "ui_login_main_dlg.h"

namespace hestina {
namespace client {
namespace ui {

login_main_dlg::login_main_dlg(QWidget* parent)
    : QDialog(parent), ui_(std::make_unique<Ui::login_main_dlg>()) {
    ui_->setupUi(this);

    // setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint);
    setWindowFlag(Qt::FramelessWindowHint);

    ui_->logo_text->setPixmap(
        QPixmap(":/login/logo_text.png")
            .scaled(ui_->logo_text->size(), Qt::KeepAspectRatio,
                Qt::SmoothTransformation));

    ui_->avatar->resize(60, 60);
    ui_->avatar->setPixmap(
        QPixmap(":/avatar/default_avatar.png")
            .scaled(ui_->avatar->size() - QSize{5, 5}, Qt::KeepAspectRatio,
                Qt::SmoothTransformation));

    ui_->password->setEchoMode(QLineEdit::EchoMode::Normal);
    ui_->account->setValidator(
        new QRegExpValidator(QRegExp("[1-9]\\d{6,10}"), this));

    ui_->password->setEchoMode(QLineEdit::EchoMode::Password);
    ui_->password->setValidator(
        new QRegExpValidator(QRegExp("\\S{1,20}"), this));

    connect(ui_->login_bnt, &QPushButton::clicked, [this]() {
        qDebug() << "account : " << ui_->account->text()
                 << "\npassward : " << ui_->password->text();
        std::cerr << "clicked" << std::endl;
    });
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
