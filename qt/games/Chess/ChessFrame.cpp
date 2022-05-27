#include "ChessFrame.h"

#include <QPainter>

#include <map>

ChessFrame::ChessFrame(QWidget *parent)
    : QFrame(parent)
    , pieces_(Piece::GetInitStatusPieces())
{
    setParent(parent);

    setFixedSize(9 * kUnitLength + 2, 10 * kUnitLength + 2);
    setStyleSheet("background-color:SandyBrown");
}

ChessFrame::~ChessFrame() = default;

void ChessFrame::drawBoard(QPainter &painter)
{
    drawBoardLine(painter);
    drawBoardText(painter);
}

void ChessFrame::drawBoardLine(QPainter &painter)
{
    QVector<QLine> linesOfAround {
        { start.x() + 0, start.y() + 0
            , start.x() + 8 * kUnitLength, start.y() + 0 },
        { start.x() + 8 * kUnitLength, start.y() + 0
            , start.x() + 8 * kUnitLength, start.y() + kUnitLength * 9 },
        { start.x() + 8 * kUnitLength, start.y() + kUnitLength * 9
            , start.x() + 0, start.y() + kUnitLength * 9 },
        { start.x() + 0, start.y() + kUnitLength * 9
            , start.x() + 0, start.y() + 0 },
    };

    QVector<QLine> linesOfVertical;
    for (int i = 0; i < 7; ++i) {
        linesOfVertical.push_back(QLine{ start.x() + (i + 1) * kUnitLength, start.y() + 0
            , start.x() + (i + 1) * kUnitLength, start.x() + 4 * kUnitLength});
        linesOfVertical.push_back(QLine{ start.x() + (i + 1) * kUnitLength, start.y() + 5 * kUnitLength
            , start.x() + (i + 1) * kUnitLength, start.x() + (4 + 5) * kUnitLength});
    }

    QVector<QLine> linesOfHorizontal;
    for (int i = 0; i < 8; ++i) {
        linesOfHorizontal.push_back(QLine{ start.x() + 0 + 1, start.y() + (i + 1) * kUnitLength
            , start.x() + 8 * kUnitLength, start.y() + (i + 1) * kUnitLength });
    }

    QVector<QLine> linesOfCross {
        { start.x() + 3 * kUnitLength, start.y() + 0 + 1
            , start.x() + 5 * kUnitLength, start.y() + 2 * kUnitLength - 1 },
        { start.x() + 5 * kUnitLength, start.y() + 0 + 1
            , start.x() + 3 * kUnitLength, start.y() + 2 * kUnitLength - 1 },
        { start.x() + 3 * kUnitLength, start.y() + 7 * kUnitLength
            , start.x() + 5 * kUnitLength, start.y() + 9 * kUnitLength - 1 },
        { start.x() + 5 * kUnitLength, start.y() + 7 * kUnitLength
            , start.x() + 3 * kUnitLength, start.y() + 9 * kUnitLength - 1 },
    };

    QVector<QLine> linesOfPoint;
    constexpr int d = 12;
    for (auto &&point : {
        QPoint{ start.x() + 1 * kUnitLength, start.y() + 2 * kUnitLength },
        QPoint{ start.x() + 7 * kUnitLength, start.y() + 2 * kUnitLength },
        QPoint{ start.x() + 2 * kUnitLength, start.y() + 3 * kUnitLength },
        QPoint{ start.x() + 4 * kUnitLength, start.y() + 3 * kUnitLength },
        QPoint{ start.x() + 6 * kUnitLength, start.y() + 3 * kUnitLength },

        QPoint{ start.x() + 1 * kUnitLength, start.y() + 7 * kUnitLength },
        QPoint{ start.x() + 7 * kUnitLength, start.y() + 7 * kUnitLength },
        QPoint{ start.x() + 2 * kUnitLength, start.y() + 6 * kUnitLength },
        QPoint{ start.x() + 4 * kUnitLength, start.y() + 6 * kUnitLength },
        QPoint{ start.x() + 6 * kUnitLength, start.y() + 6 * kUnitLength },
    }) {

        linesOfPoint.push_back(QLine{ point.x() - 4, point.y() - d, point.x() - 4, point.y() - 4 });
        linesOfPoint.push_back(QLine{ point.x() - 4, point.y() + d, point.x() - 4, point.y() + 4 });
        linesOfPoint.push_back(QLine{ point.x() + 4, point.y() - d, point.x() + 4, point.y() - 4 });
        linesOfPoint.push_back(QLine{ point.x() + 4, point.y() + d, point.x() + 4, point.y() + 4 });

        linesOfPoint.push_back(QLine{ point.x() - d, point.y() - 4, point.x() - 4, point.y() - 4 });
        linesOfPoint.push_back(QLine{ point.x() - d, point.y() + 4, point.x() - 4, point.y() + 4 });
        linesOfPoint.push_back(QLine{ point.x() + d, point.y() - 4, point.x() + 4, point.y() - 4 });
        linesOfPoint.push_back(QLine{ point.x() + d, point.y() + 4, point.x() + 4, point.y() + 4 });
    }
    for (auto &&point : {
        QPoint{ start.x() + 0 * kUnitLength, start.y() + 3 * kUnitLength },
        QPoint{ start.x() + 0 * kUnitLength, start.y() + 6 * kUnitLength },
    }) {

        linesOfPoint.push_back(QLine{ point.x() + 4, point.y() - d, point.x() + 4, point.y() - 4 });
        linesOfPoint.push_back(QLine{ point.x() + 4, point.y() + d, point.x() + 4, point.y() + 4 });

        linesOfPoint.push_back(QLine{ point.x() + d, point.y() - 4, point.x() + 4, point.y() - 4 });
        linesOfPoint.push_back(QLine{ point.x() + d, point.y() + 4, point.x() + 4, point.y() + 4 });
    }
    for (auto &&point : {
        QPoint{ start.x() + 8 * kUnitLength, start.y() + 3 * kUnitLength },
        QPoint{ start.x() + 8 * kUnitLength, start.y() + 6 * kUnitLength },
    }) {

        linesOfPoint.push_back(QLine{ point.x() - 4, point.y() - d, point.x() - 4, point.y() - 4 });
        linesOfPoint.push_back(QLine{ point.x() - 4, point.y() + d, point.x() - 4, point.y() + 4 });

        linesOfPoint.push_back(QLine{ point.x() - d, point.y() - 4, point.x() - 4, point.y() - 4 });
        linesOfPoint.push_back(QLine{ point.x() - d, point.y() + 4, point.x() - 4, point.y() + 4 });
    }

    painter.drawLines(linesOfAround);
    painter.drawLines(linesOfVertical);
    painter.drawLines(linesOfHorizontal);
    painter.drawLines(linesOfCross);
    painter.drawLines(linesOfPoint);
}

void ChessFrame::drawBoardText(QPainter &painter)
{
    QFont font;
    font.setFamily(u8"隶书");
    font.setPixelSize(kUnitLength - 5);
    painter.setFont(font);

    painter.translate(QPoint{ start.x() + 1 * kUnitLength + kUnitLength / 2, start.y() + 4 * kUnitLength + kUnitLength / 2 });
    painter.rotate(-90);
    painter.drawText(QRect{ { -kUnitLength / 2, -kUnitLength / 2 }
            , QSize{ kUnitLength, kUnitLength } }
        , Qt::AlignBottom | Qt::AlignHCenter, u8"楚");
    painter.resetTransform();

    painter.translate(QPoint{ start.x() + 2 * kUnitLength + kUnitLength / 2, start.y() + 4 * kUnitLength + kUnitLength / 2 });
    painter.rotate(-90);
    painter.drawText(QRect{ { -kUnitLength / 2, -kUnitLength / 2 }
            , QSize{ kUnitLength, kUnitLength } }
        , Qt::AlignTop | Qt::AlignHCenter, u8"河");
    painter.resetTransform();

    painter.translate(QPoint{ start.x() + 5 * kUnitLength + kUnitLength / 2, start.y() + 4 * kUnitLength + kUnitLength / 2 });
    painter.rotate(+90);
    painter.drawText(QRect{ { -kUnitLength / 2, -kUnitLength / 2 }
            , QSize{ kUnitLength, kUnitLength } }
        , Qt::AlignTop | Qt::AlignHCenter, u8"界");
    painter.resetTransform();

    painter.translate(QPoint{ start.x() + 6 * kUnitLength + kUnitLength / 2, start.y() + 4 * kUnitLength + kUnitLength / 2 });
    painter.rotate(+90);
    painter.drawText(QRect{ { -kUnitLength / 2, -kUnitLength / 2 }
            , QSize{ kUnitLength, kUnitLength } }
        , Qt::AlignBottom | Qt::AlignHCenter, u8"漢");
    painter.resetTransform();
}
void ChessFrame::drawPiece(QPainter &painter)
{
    for (auto && [point, piece] : pieces_) {
        piece.draw(point, painter);
    }
}

void ChessFrame::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 2));
    painter.setRenderHint(QPainter::Antialiasing, true);

    drawBoard(painter);
    drawPiece(painter);
}
