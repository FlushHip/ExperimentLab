#include "gotocelldialog.h"

#include <QRegExpValidator>
#include <QPushButton>

#include "ui_gotocelldialog.h"

GoToCellDialog::GoToCellDialog(QWidget *parent)
    : QDialog(parent)
    , ui_(std::make_unique<Ui::GoToCellDialog>())
{
    ui_->setupUi(this);

    ui_->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    QRegExp regExp("[A-Za-z][1-9][0-9]{0,2}");
    ui_->lineEdit->setValidator(new QRegExpValidator(regExp, this));
}

GoToCellDialog::~GoToCellDialog() = default;

void GoToCellDialog::on_lineEdit_textChanged()
{
    ui_->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(ui_->lineEdit->hasAcceptableInput());
}
