#include "finddialog.h"

#include <QDebug>

#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

struct FindDialog::ImplData
{
    QLabel *label;
    QLineEdit *lineEdit;
    QCheckBox *caseCheckBox, *backwardCheckBox;
    QPushButton *findBtn, *closeBtn;
};

FindDialog::FindDialog(QWidget *parent)
    : QDialog(parent)
    , implData_(std::make_unique<ImplData>())
{
    implData_->label = new QLabel(tr("Find &what:"));
    implData_->lineEdit = new QLineEdit;
    implData_->label->setBuddy(implData_->lineEdit);

    implData_->caseCheckBox = new QCheckBox(tr("Match &case"));
    implData_->backwardCheckBox = new QCheckBox(tr("Search &backward"));

    implData_->findBtn = new QPushButton(tr("&Find"));
    implData_->findBtn->setDefault(true);
    implData_->findBtn->setEnabled(false);
    implData_->closeBtn = new QPushButton(tr("Close"));

    connect(implData_->lineEdit, &QLineEdit::textChanged, [this](const QString &text)
    {
        implData_->findBtn->setEnabled(!text.isEmpty());

        qDebug() << text << Qt::endl;
    });
    connect(implData_->findBtn, &QPushButton::clicked, this, &FindDialog::onFindBtnClicked);
    connect(implData_->closeBtn, &QPushButton::clicked, this, &FindDialog::close);

    auto topLeftLayout = new QHBoxLayout;
    topLeftLayout->addWidget(implData_->label);
    topLeftLayout->addWidget(implData_->lineEdit);

    auto leftLayout = new QVBoxLayout;
    leftLayout->addLayout(topLeftLayout);
    leftLayout->addWidget(implData_->caseCheckBox);
    leftLayout->addWidget(implData_->backwardCheckBox);

    auto rightLayout = new QVBoxLayout;
    rightLayout->addWidget(implData_->findBtn);
    rightLayout->addWidget(implData_->closeBtn);
    rightLayout->addStretch();

    auto mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    setLayout(mainLayout);

    setWindowTitle(tr("Find"));
    setFixedHeight(sizeHint().height());
}

FindDialog::~FindDialog() = default;

void FindDialog::onFindBtnClicked()
{
    QString text = implData_->lineEdit->text();

    Qt::CaseSensitivity cs = implData_->caseCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;

    if (implData_->backwardCheckBox->isChecked()) {
        emit findNext(text, cs);
    } else {
        emit findPrevious(text, cs);
    }

    qDebug() << text << " : " << cs << Qt::endl;
}
