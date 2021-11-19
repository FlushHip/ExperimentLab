#pragma once

#include <QDialog>

namespace Ui
{
class GoToCellDialog;
}

class GoToCellDialog : public QDialog
{
    Q_OBJECT
public:
    explicit GoToCellDialog(QWidget *parent = Q_NULLPTR);
    ~GoToCellDialog() override;

private slots:
    void on_lineEdit_textChanged();

private:
    std::unique_ptr<Ui::GoToCellDialog> ui_;
};
