#include "ChessFrame.h"

#include <QPainter>

ChessFrame::ChessFrame(QWidget *parent)
    : QFrame(parent)
{
    setParent(parent);
}

ChessFrame::~ChessFrame() = default;

void ChessFrame::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 2));

    int unit = (width() - 2) / 8;
    QVector<QLine> linesOfAround {
        { 0 + 1, 0 + 1, 8 * unit - 1, 0 + 1 },
        { 8 * unit - 1, 0 + 1, 8 * unit - 1, unit * 9 - 1 },
        { 8 * unit - 1, unit * 9 - 1, 0 + 1, unit * 9 - 1 },
        { 0 + 1, unit * 9 - 1, 0 + 1, 0 + 1 },
    };

    QVector<QLine> linesOfVertical;
    for (int i = 0; i < 7; ++i) {
        linesOfVertical.push_back(QLine{ (i + 1) * unit, 0, (i + 1) * unit, 4 * unit});
        linesOfVertical.push_back(QLine{ (i + 1) * unit, 5 * unit, (i + 1) * unit, (4 + 5) * unit - 1});
    }

    QVector<QLine> linesOfHorizontal;
    for (int i = 0; i < 8; ++i) {
        linesOfHorizontal.push_back(QLine{ 0, (i + 1) * unit, 8 * unit - 1, (i + 1) * unit });
    }

    QVector<QLine> linesOfCross {
        { 3 * unit, 0 + 1, 5 * unit, 2 * unit },
        { 5 * unit, 0 + 1, 3 * unit, 2 * unit },
        { 3 * unit, 7 * unit, 5 * unit, 9 * unit - 1 },
        { 5 * unit, 7 * unit, 3 * unit, 9 * unit - 1 },
    };

    QVector<QLine> linesOfPoint;
    for (auto &&point : {
        QPoint{ 1 * unit, 2 * unit },
        QPoint{ 7 * unit, 2 * unit },
        QPoint{ 0 * unit + 1, 3 * unit },
        QPoint{ 2 * unit, 3 * unit },
        QPoint{ 4 * unit, 3 * unit },
        QPoint{ 6 * unit, 3 * unit },
        QPoint{ 8 * unit - 1, 3 * unit },

        QPoint{ 1 * unit, 7 * unit },
        QPoint{ 7 * unit, 7 * unit },
        QPoint{ 0 * unit + 1, 6 * unit },
        QPoint{ 2 * unit, 6 * unit },
        QPoint{ 4 * unit, 6 * unit },
        QPoint{ 6 * unit, 6 * unit },
        QPoint{ 8 * unit - 1, 6 * unit },
    }) {
        static constexpr int d = 12;

        linesOfPoint.push_back(QLine{ point.x() - 4, point.y() - d, point.x() - 4, point.y() - 4 });
        linesOfPoint.push_back(QLine{ point.x() - 4, point.y() + d, point.x() - 4, point.y() + 4 });
        linesOfPoint.push_back(QLine{ point.x() + 4, point.y() - d, point.x() + 4, point.y() - 4 });
        linesOfPoint.push_back(QLine{ point.x() + 4, point.y() + d, point.x() + 4, point.y() + 4 });

        linesOfPoint.push_back(QLine{ point.x() - d, point.y() - 4, point.x() - 4, point.y() - 4 });
        linesOfPoint.push_back(QLine{ point.x() - d, point.y() + 4, point.x() - 4, point.y() + 4 });
        linesOfPoint.push_back(QLine{ point.x() + d, point.y() - 4, point.x() + 4, point.y() - 4 });
        linesOfPoint.push_back(QLine{ point.x() + d, point.y() + 4, point.x() + 4, point.y() + 4 });
    }

    painter.drawLines(linesOfAround);
    painter.drawLines(linesOfVertical);
    painter.drawLines(linesOfHorizontal);
    painter.drawLines(linesOfCross);
    painter.drawLines(linesOfPoint);

}
