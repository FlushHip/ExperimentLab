#pragma once

#include <QDialog>

namespace Ui {
class login_main_dlg;
}  // namespace Ui

namespace hestina {
namespace client {
namespace ui {

class login_main_dlg : public QDialog {
    Q_OBJECT
public:
    login_main_dlg(QWidget* parent = nullptr);
    ~login_main_dlg() override;

private:
    std::unique_ptr<Ui::login_main_dlg> ui_;
};

}  // namespace ui
}  // namespace client
}  // namespace hestina
