#pragma once

#include <QLCDNumber>

#include <chrono>

class TimeFrame : public QLCDNumber {
    Q_OBJECT
public:
    explicit TimeFrame(QWidget *parent = nullptr);
    ~TimeFrame() override;

private slots:
    void showTime();

private:
    std::chrono::steady_clock::time_point begin_;
};
