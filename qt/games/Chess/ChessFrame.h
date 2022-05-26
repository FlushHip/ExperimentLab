#pragma once

#include <QFrame>

#include "Piece.h"
#include "common_define.h"

class ChessFrame : public QFrame {
    Q_OBJECT
public:
    explicit ChessFrame(QWidget *parent = nullptr);
    ~ChessFrame() override;

protected:
    void paintEvent(QPaintEvent *) override;

private:
    void drawBoard(QPainter &painter);
    void drawBoardLine(QPainter &painter);
    void drawBoardText(QPainter &patiner);

private:
    const QPoint start{ kUnitLength / 2, kUnitLength / 2 };
    std::map<Point, Piece> pieces_;
};
