#pragma once

#include <QWidget>

class ChessFrame;
class TimeFrame;
class GainFrame;

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    ChessFrame *chessFrame_;
    TimeFrame *timeFrame_;
    GainFrame *gainFrame_[2];
};
