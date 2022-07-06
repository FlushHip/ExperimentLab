#pragma once

#include <QLCDNumber>

#include <chrono>

#include "Piece.h"

class TimeFrame : public QLCDNumber {
    Q_OBJECT
public:
    explicit TimeFrame(QWidget *parent = nullptr);
    ~TimeFrame() override;

public slots:
    void changeBackgroundColor(PieceBi turn);

private slots:
    void showTime();

private:
    std::chrono::steady_clock::time_point begin_;
};
