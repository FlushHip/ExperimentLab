#include "login_main_dlg.h"

#include <memory>

#include "ui_login_main_dlg.h"

namespace hestina {
namespace client {
namespace ui {

login_main_dlg::login_main_dlg(QWidget* parent)
    : QDialog(parent), ui_(std::make_unique<Ui::login_main_dlg>()) {
    ui_->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint);
}

login_main_dlg::~login_main_dlg() = default;

}  // namespace ui
}  // namespace client
}  // namespace hestina
