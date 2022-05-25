#pragma once

#include <QFrame>

class ChessFrame : public QFrame {
    Q_OBJECT
public:
    explicit ChessFrame(QWidget *parent = nullptr);
    ~ChessFrame() override;

protected:
    void paintEvent(QPaintEvent *) override;

private:
};
