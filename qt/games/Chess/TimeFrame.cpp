#include "TimeFrame.h"

#include <QTimer>

TimeFrame::TimeFrame(QWidget *parent)
    : QLCDNumber(parent)
    , begin_(std::chrono::steady_clock::now())
{
    setParent(parent);
    setDigitCount(5);

    auto timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &TimeFrame::showTime);
    using namespace std::literals::chrono_literals;
    timer->start(1000ms);

    showTime();
}

TimeFrame::~TimeFrame() = default;

void TimeFrame::showTime()
{
    auto nowTime = std::chrono::steady_clock::now();
    int second = std::chrono::duration_cast<std::chrono::seconds>(nowTime - begin_).count();
}
