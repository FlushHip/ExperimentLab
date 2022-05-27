#include "TimeFrame.h"

#include <QTimer>

#include <sstream>
#include <iomanip>

#include "common_define.h"

TimeFrame::TimeFrame(QWidget *parent)
    : QLCDNumber(parent)
    , begin_(std::chrono::steady_clock::now())
{
    setParent(parent);
    setDigitCount(5);
    setSegmentStyle(QLCDNumber::Filled);

    auto timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &TimeFrame::showTime);
    using namespace std::literals::chrono_literals;
    timer->start(1000ms);

    showTime();

    setStyleSheet("background-color:SandyBrown");
}

TimeFrame::~TimeFrame() = default;

void TimeFrame::showTime()
{
    auto nowTime = std::chrono::steady_clock::now();
    int second = std::chrono::duration_cast<std::chrono::seconds>(nowTime - begin_).count();

    auto fn = [] (int digits) {
        std::stringstream sin;
        sin << std::setw(2) << std::setfill('0') << digits;
        return sin.str();
    };
    auto str =  fn(second / 60) + ":" + fn(second % 60);
    display(QString::fromStdString(str));
}
void TimeFrame::changeBackgroundColor(PieceBi turn)
{
    if (turn == PieceBi::kBlack) {
        setStyleSheet("background-color:black");
    } else {
        setStyleSheet("background-color:red");
    }
}
