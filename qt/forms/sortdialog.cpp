#include "sortdialog.h"

#include "ui_sortdialog.h"

SortDialog::SortDialog(QWidget *parent)
    : QDialog(parent)
    , ui_(std::make_unique<Ui::SortDialog>())
{
    ui_->setupUi(this);

    ui_->groupBox_2->hide();
    ui_->groupBox_3->hide();

    layout()->setSizeConstraint(QLayout::SetFixedSize);

    setColumnRange('A', 'Z');
}

SortDialog::~SortDialog() = default;

void SortDialog::setColumnRange(QChar first, QChar last)
{
    ui_->comboBoxColumn_1->clear();
    ui_->comboBoxColumn_2->clear();
    ui_->comboBoxColumn_3->clear();

    ui_->comboBoxColumn_2->addItem(tr("None"));
    ui_->comboBoxColumn_3->addItem(tr("None"));
    ui_->comboBoxColumn_1->setMinimumSize(ui_->comboBoxColumn_2->sizeHint());

    for (auto c = first; c <= last; c = c.unicode() + 1) {
        ui_->comboBoxColumn_1->addItem(QString(c));
        ui_->comboBoxColumn_2->addItem(QString(c));
        ui_->comboBoxColumn_3->addItem(QString(c));
    }
}
