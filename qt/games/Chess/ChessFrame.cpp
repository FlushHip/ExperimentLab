#include "ChessFrame.h"

#include <QPainter>
#include <QMouseEvent>
#include <QtDebug>
#include <QCursor>
#include <QRandomGenerator>

#include <map>
#include <numeric>

ChessFrame::ChessFrame(QWidget *parent)
    : QFrame(parent)
    , pieces_(Piece::GetInitStatusPieces())
    , choosePiecePoint_(std::numeric_limits<char>::max(), std::numeric_limits<char>::max())
    , status_(Status::None)
    , turn_(static_cast<PieceBi>(QRandomGenerator::global()->bounded(2)))
{
    setParent(parent);

    setFixedSize(9 * kUnitLength + 2, 11 * kUnitLength + 2);
    //setStyleSheet("background-color:SandyBrown");
    setCursor(Qt::OpenHandCursor);
}

ChessFrame::~ChessFrame() = default;

void ChessFrame::startFrame()
{
    emit turnChanged(turn_);
}

void ChessFrame::drawBoard(QPainter &painter)
{
    drawBoardBackground(painter);
    drawBoardLine(painter);
    drawBoardText(painter);
}

void ChessFrame::drawBoardBackground(QPainter &painter)
{
    QBrush brush(qRgb(244, 164, 96), Qt::Dense1Pattern);
    painter.fillRect(0, kUnitLength / 2,  9 * kUnitLength, 10 * kUnitLength
        , brush);
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
            , start.x() + (i + 1) * kUnitLength, start.y() + 4 * kUnitLength});
        linesOfVertical.push_back(QLine{ start.x() + (i + 1) * kUnitLength, start.y() + 5 * kUnitLength
            , start.x() + (i + 1) * kUnitLength, start.y() + (4 + 5) * kUnitLength});
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


    static const QString sPiecePointDigit[][9] = {
        { u8"一", u8"二", u8"三", u8"四", u8"五", u8"六", u8"七", u8"八", u8"九" },
        { u8"1", u8"2", u8"3", u8"4", u8"5", u8"6", u8"7", u8"8", u8"9" },
    };

    font.setFamily(u8"Lucida Console");
    font.setPixelSize(kUnitLength / 2 - 8);
    painter.setFont(font);
    for (int i = 0; i < 9; ++i) {
        painter.drawText(QRect{ { start.x() + i * kUnitLength - kUnitLength / 4, 0 }
                , QSize{ kUnitLength / 2, kUnitLength / 2 } }
            , Qt::AlignCenter, sPiecePointDigit[static_cast<int>(PieceBi::kBlack)][i]);
    }

    font.setFamily(u8"隶书");
    font.setPixelSize(kUnitLength / 2 - 5);
    painter.setFont(font);
    for (int i = 8; i >= 0; --i) {
        painter.drawText(QRect{ { start.x() + i * kUnitLength - kUnitLength / 4, start.y() + 9 * kUnitLength + kUnitLength / 2 }
                , QSize{ kUnitLength / 2, kUnitLength / 2 } }
            , Qt::AlignCenter, sPiecePointDigit[static_cast<int>(PieceBi::kRed)][8 - i]);
    }
}
void ChessFrame::drawPieces(QPainter &painter)
{
    for (auto && [point, piece] : pieces_) {
        if (!piece.choosed()) {
            painter.drawPixmap(start.x() + point.first * kUnitLength - kUnitLength / 2
                        , start.y() + point.second * kUnitLength - kUnitLength / 2, piece.pixmap());
        }
    }
}

void ChessFrame::drawMovingPiece(QPainter &painter)
{
    if (status_ == Status::Moving) {
        painter.drawPixmap(curMovingPiecePos_ - QPoint{ kUnitLength / 2, kUnitLength / 2 }
            , pieces_[choosePiecePoint_].pixmap());
    }
}

void ChessFrame::drawPieceRect(QPainter &painter, Point point, QColor color, int hegith)
{
    painter.setPen(QPen(color, hegith));
    painter.drawLine(start.x() + point.first * kUnitLength - kUnitLength / 2, start.y() + point.second * kUnitLength  - kUnitLength / 2
        , start.x() + point.first * kUnitLength - kUnitLength / 2 + 4, start.y() + point.second * kUnitLength  - kUnitLength / 2);
    painter.drawLine(start.x() + point.first * kUnitLength + kUnitLength / 2, start.y() + point.second * kUnitLength  - kUnitLength / 2
        , start.x() + point.first * kUnitLength + kUnitLength / 2 - 4, start.y() + point.second * kUnitLength  - kUnitLength / 2);
    painter.drawLine(start.x() + point.first * kUnitLength - kUnitLength / 2, start.y() + point.second * kUnitLength  + kUnitLength / 2
        , start.x() + point.first * kUnitLength - kUnitLength / 2 + 4, start.y() + point.second * kUnitLength  + kUnitLength / 2);
    painter.drawLine(start.x() + point.first * kUnitLength + kUnitLength / 2, start.y() + point.second * kUnitLength  + kUnitLength / 2
        , start.x() + point.first * kUnitLength + kUnitLength / 2 - 4, start.y() + point.second * kUnitLength  + kUnitLength / 2);

    painter.drawLine(start.x() + point.first * kUnitLength - kUnitLength / 2, start.y() + point.second * kUnitLength  - kUnitLength / 2
        , start.x() + point.first * kUnitLength - kUnitLength / 2, start.y() + point.second * kUnitLength  - kUnitLength / 2 + 4);
    painter.drawLine(start.x() + point.first * kUnitLength - kUnitLength / 2, start.y() + point.second * kUnitLength  + kUnitLength / 2
        , start.x() + point.first * kUnitLength - kUnitLength / 2, start.y() + point.second * kUnitLength  + kUnitLength / 2 - 4);
    painter.drawLine(start.x() + point.first * kUnitLength + kUnitLength / 2, start.y() + point.second * kUnitLength  - kUnitLength / 2
        , start.x() + point.first * kUnitLength + kUnitLength / 2, start.y() + point.second * kUnitLength  - kUnitLength / 2 + 4);
    painter.drawLine(start.x() + point.first * kUnitLength + kUnitLength / 2, start.y() + point.second * kUnitLength  + kUnitLength / 2
        , start.x() + point.first * kUnitLength + kUnitLength / 2, start.y() + point.second * kUnitLength  + kUnitLength / 2 - 4);
}

void ChessFrame::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 2));
    painter.setRenderHint(QPainter::Antialiasing, true);

    drawBoard(painter);
    drawPieces(painter);

    drawMovingPiece(painter);

    drawPiecePath(painter);
}

void ChessFrame::drawPiecePath(QPainter &painter)
{
    if (preMovePath_) {
        drawPieceRect(painter, preMovePath_->first, Qt::blue, 2);
        drawPieceRect(painter, preMovePath_->second, Qt::blue, 2);
    }
    drawPieceRect(painter, choosePiecePoint_, Qt::red, 2);
    if (status_ == Status::Moving) {
        drawPieceRect(painter
            , { (curMovingPiecePos_.x() - start.x() + kUnitLength / 2) / kUnitLength
                , (curMovingPiecePos_.y() - start.y() + kUnitLength / 2) / kUnitLength }
            , Qt::red
            , 2);
    }
}

void ChessFrame::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MouseButton::LeftButton
        || event->button() == Qt::MouseButton::RightButton) {
        auto plantPos = event->pos() - start;
        Point curPoint = { (plantPos.x() + kUnitLength / 2) / kUnitLength
                        , (plantPos.y() + kUnitLength / 2) / kUnitLength };
        switch (status_)
        {
        case Status::None:
            if (auto it = pieces_.find(curPoint)
                ; it != pieces_.end() && it->second.bi() == turn_) {
                status_ = Status::ClickedPiece;
                choosePiecePoint_ = curPoint;
                it->second.setChoosed(true);
                setCursor(Qt::ClosedHandCursor);
                status_ = Status::Moving;
            }
            break;
        case Status::Moving:
            if (pieces_.find(curPoint) != pieces_.end()) {
                status_ = Status::None;
                setCursor(Qt::OpenHandCursor);
            }
            break;

        default:
            break;
        }
    }
}

void ChessFrame::mouseReleaseEvent(QMouseEvent *event)
{
    if (status_ == Status::Moving) {
        status_ = Status::None;
        pieces_[choosePiecePoint_].setChoosed(false);
        setCursor(Qt::OpenHandCursor);

        auto plantPos = event->pos() - start;
        Point curPoint = { (plantPos.x() + kUnitLength / 2) / kUnitLength
                        , (plantPos.y() + kUnitLength / 2) / kUnitLength };

        if (tryMove(curPoint)) {
            auto prePiece = pieces_[choosePiecePoint_];
            if (auto it = pieces_.find(curPoint); it != pieces_.end() && it->second.bi() != prePiece.bi()) {
                emit pieceEated(it->second);

                pieces_.erase(it);
            }
            pieces_.erase(choosePiecePoint_);
            pieces_.emplace(std::move(curPoint), std::move(prePiece));

            movedPiecePoint_ = curPoint;

            preMovePath_ = { choosePiecePoint_, movedPiecePoint_ };

            qDebug() << (turn_ == PieceBi::kBlack
                    ? QT_STRINGIFY(PieceBi::kBlack)
                    : QT_STRINGIFY(PieceBi::kRed)) << " : "
                << preMovePath_->first << " -> " << preMovePath_->second;

            choosePiecePoint_ = { std::numeric_limits<char>::max(), std::numeric_limits<char>::max() };

            turn_ = turn_ == PieceBi::kBlack ? PieceBi::kRed : PieceBi::kBlack;
            emit turnChanged(turn_);
        }

        update();
    }
}

void ChessFrame::mouseMoveEvent(QMouseEvent *event)
{
    if (status_ == Status::Moving) {
        curMovingPiecePos_ = event->pos();
        update();
    }
}

int ChessFrame::transformX(int x)
{
    if (turn_ == PieceBi::kRed) {
        return 8 - x;
    }
    return x;
}

int ChessFrame::transformY(int y)
{
    if (turn_ == PieceBi::kRed) {
        return 9 - y;
    }
    return y;
}

Point ChessFrame::transformPoint(const Point &point)
{
    return { transformX(point.first), transformY(point.second) };
}

bool ChessFrame::tryMove(const Point &targetPoint)
{
    auto srcPiece = pieces_[choosePiecePoint_];
    auto srcPoint = choosePiecePoint_;
    auto desPoint = targetPoint;

    if (desPoint.first < 0 || desPoint.second < 0
        || desPoint.first > 8 || desPoint.second > 9
        || srcPoint == desPoint
        || (pieces_.find(desPoint) != pieces_.end()
            && srcPiece.bi() == pieces_[desPoint].bi())) {
        return false;
    }

    switch (srcPiece.type()) {
    case PieceType::kG:
        if (!QRect{ QPoint{ 3, 0 }, QSize{ 3, 3 } }.contains(transformX(desPoint.first), transformY(desPoint.second))) {
            return false;
        }
        for (auto &&[dir_x, dir_y] : { Point{ 0, 1 }, Point{ 0, -1 }, Point{ 1, 0 }, Point{ -1, 0 } }) {
            if (desPoint == Point{ srcPoint.first + dir_x, srcPoint.second + dir_y }) {
                return true;
            }
        }
        return false;
        break;

    case PieceType::kA:
        for (auto &&point : { Point{ 3, 0 }, Point{ 5, 0 }
            , Point{ 4, 1 }
            , Point{ 3, 2 }, Point{ 5, 2 } }) {
            if (point == transformPoint(desPoint)
                && std::abs(desPoint.first - srcPoint.first) == 1
                    && std::abs(desPoint.second - srcPoint.second) == 1) {
                return true;
            }
        }
        return false;
    case PieceType::kE:
        for (auto &&point : { Point{ 2, 0 }, Point{ 6, 0 }
            , Point{ 0, 2 }, Point{ 4, 2 }, Point{ 8, 2 }
            , Point{ 2, 4 }, Point{ 6, 4 } }) {
            if (point == transformPoint(desPoint)
                && std::abs(desPoint.first - srcPoint.first) == 2
                    && std::abs(desPoint.second - srcPoint.second) == 2
                && pieces_.end() == pieces_.find({ (srcPoint.first + desPoint.first) / 2
                                    , (srcPoint.second + desPoint.second) / 2 })) {
                return true;
            }
        }
        return false;
    case PieceType::kH:
        for (auto &&[dir_x, dir_y] : { Point{ 1, 2 }, Point{ 1, -2}
            , Point{ 2, 1 }, Point{ 2, -1 }
            , Point{ -1, 2}, Point{ -1, -2 }
            , Point{ -2, 1 }, Point{ -2, -1 } }) {
            if (auto obstaclePoint = Point{ srcPoint.first + (std::abs(dir_x) == 2 ? dir_x / 2 : 0)
                                            , srcPoint.second + (std::abs(dir_y) == 2 ? dir_y / 2 : 0) }
                , toPoint = Point{ srcPoint.first + dir_x, srcPoint.second + dir_y }
                ; toPoint == desPoint && pieces_.end() == pieces_.find(obstaclePoint)) {
                return true;
            }
        }
        return false;
    case PieceType::kR: {
        if (!(srcPoint.first == desPoint.first || srcPoint.second == desPoint.second)) {
            return false;
        }
        int cnt = 0;
        for (int i = std::min(desPoint.first, srcPoint.first)
            ; i <= std::max(desPoint.first, srcPoint.first); ++i) {
            for (int j = std::min(desPoint.second, srcPoint.second)
                ; j <= std::max(desPoint.second, srcPoint.second); ++j) {
                if (pieces_.end() != pieces_.find({ i, j })) {
                    ++cnt;
                }
            }
        }
        return cnt == (1 + (pieces_.end() != pieces_.find(desPoint)));
    }
    case PieceType::kC: {
        if (!(srcPoint.first == desPoint.first || srcPoint.second == desPoint.second)) {
            return false;
        }
        int cnt = 0;
        for (int i = std::min(desPoint.first, srcPoint.first)
            ; i <= std::max(desPoint.first, srcPoint.first); ++i) {
            for (int j = std::min(desPoint.second, srcPoint.second)
                ; j <= std::max(desPoint.second, srcPoint.second); ++j) {
                if (pieces_.end() != pieces_.find({ i, j })) {
                    ++cnt;
                }
            }
        }
        if (cnt == 1) {
            return pieces_.end() == pieces_.find(desPoint);
        }
        return (pieces_.end() != pieces_.find(desPoint)) && cnt == 1 + 1 + 1;
    }
    case PieceType::kS:
        if (transformY(desPoint.second) < 5) {
            return transformY(desPoint.second) - transformY(srcPoint.second) == 1 && desPoint.first == srcPoint.first;
        }
        for (auto &&[dir_x, dir_y] : { Point{ 1, 0 }, Point{ -1, 0 }, Point{ 0, 1 } }) {
            if (desPoint == transformPoint(Point{ transformX(srcPoint.first) + dir_x, transformY(srcPoint.second) + dir_y })) {
                return true;
            }
        }
        return false;

    default:
        break;
    }

    return true;
}
