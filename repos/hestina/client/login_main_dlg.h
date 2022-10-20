#pragma once

#include <qpixmap.h>
#include <qpoint.h>
#include <qwidget.h>
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

    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    std::unique_ptr<Ui::login_main_dlg> ui_;
    bool is_pressed_{false};
    QPoint pre_move_point_;
};

}  // namespace ui
}  // namespace client
}  // namespace hestina
