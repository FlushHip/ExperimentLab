#pragma once

#include <QDialog>

namespace Ui
{
class SortDialog;
} // namespace Ui

class SortDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SortDialog(QWidget *parent = Q_NULLPTR);
    ~SortDialog() override;

    void setColumnRange(QChar first, QChar last);

private:
    std::unique_ptr<Ui::SortDialog> ui_;
};
