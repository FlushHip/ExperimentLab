#pragma once

#include <QFrame>

#include <optional>

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
    void drawPieces(QPainter &painter);
    void drawMovingPiece(QPainter &painter);

    void drawPieceRect(QPainter &patiner, Point point, QColor color, int height);

    bool tryMove(const Point &targetPoint);

    int transformX(int x);
    int transformY(int y);
    Point transformPoint(const Point &point);

signals:
    void turnChanged(PieceBi turn);
    void pieceEated(Piece piece);

private:
    enum class Status{
        None,
        ClickedPiece,
        Moving,
    };
    const QPoint start{ kUnitLength / 2, kUnitLength };
    std::map<Point, Piece> pieces_;
    Point choosePiecePoint_;
    Point movedPiecePoint_;
    std::optional<std::pair<Point, Point>> preMovePath_;
    QPoint curMovingPiecePos_;
    Status status_;
    PieceBi turn_;
};
