#pragma once

#include <QWidget>

class ChessFrame;

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    ChessFrame *chessFrame_;
};
