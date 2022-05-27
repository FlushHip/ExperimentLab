#pragma once

#include <QFrame>

#include "Piece.h"
#include "common_define.h"

class ChessFrame : public QFrame {
    Q_OBJECT
public:
    explicit ChessFrame(QWidget *parent = nullptr);
    ~ChessFrame() override;

public:
    void startFrame();

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    void drawBoard(QPainter &painter);
    void drawBoardLine(QPainter &painter);
    void drawBoardText(QPainter &patiner);
    void drawPiece(QPainter &painter);

    bool tryMove(const Point &targetPoint);

    int transformX(int x);
    int transformY(int y);
    Point transformPoint(const Point &point);

signals:
    void turnChanged(PieceBi turn);

private:
    enum class Status{
        None,
        ClickedPiece,
        Moving,
    };
    const QPoint start{ kUnitLength / 2, kUnitLength / 2 };
    std::map<Point, Piece> pieces_;
    Point choosePiecePoint_;
    QPoint curMovingPiecePos_;
    Status status_;
    PieceBi turn_;
};
