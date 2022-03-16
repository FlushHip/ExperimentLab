#pragma once

#include <QDialog>

class FindDialog : public QDialog
{
    Q_OBJECT
public:
    explicit FindDialog(QWidget *parent = Q_NULLPTR);
    ~FindDialog() override;

signals:
    void findNext(const QString &str, Qt::CaseSensitivity cs);
    void findPrevious(const QString &str, Qt::CaseSensitivity cs);

private:
    void onFindBtnClicked();

private:
    struct ImplData;
    std::unique_ptr<ImplData> implData_;
};
