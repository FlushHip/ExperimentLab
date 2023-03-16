#include "GainFrame.h"

#include <QPainter>

GainFrame::GainFrame(PieceBi flag, QWidget *parent)
    : flag_(flag)
    , QFrame(parent)
{
    setParent(parent);

    setFixedSize({ 3 * kDiamter + 12 + 8, 5 * kDiamter + 12 + 12});
}

GainFrame::~GainFrame() = default;


void GainFrame::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(QPen(Qt::black, 4));
    painter.drawLine(0 + 2, 0 + 2, 3 * kDiamter + 10 + 8, 0 + 2);
    painter.drawLine(3 * kDiamter + 10 + 8, 0 + 2, 3 * kDiamter + 10 + 8, 5 * kDiamter + 10 + 12);
    painter.drawLine(3 * kDiamter + 10 + 8, 5 * kDiamter + 10 + 12, 0 + 2, 5 * kDiamter + 10 + 12);
    painter.drawLine(0 + 2, 5 * kDiamter + 10 + 12, 0 + 2, 0 + 2);

    painter.setPen(QPen(Qt::black, 1));
    painter.drawLine(0 + 6, 0 + 6, 3 * kDiamter + 6 + 8, 0 + 6);
    painter.drawLine(3 * kDiamter + 6 + 8, 0 + 6, 3 * kDiamter + 6 + 8, 5 * kDiamter + 6 + 12);
    painter.drawLine(3 * kDiamter + 6 + 8, 5 * kDiamter + 6 + 12, 0 + 6, 5 * kDiamter + 6 + 12);
    painter.drawLine(0 + 6, 5 * kDiamter + 6 + 12, 0 + 6, 0 + 6);

    const QPoint start{ 6, 6 };

    QPen penDash(flag_  == PieceBi::kBlack ? Qt::black : Qt::red, 1);
    penDash.setStyle(Qt::PenStyle::DotLine);
    painter.setPen(penDash);

    auto itOfPieces = pieces_.begin();
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 3; ++j) {
            auto rect = QRect{ start + QPoint{ j * kDiamter + (j + 1) * 2, i * kDiamter + (i + 1) * 2 }
                    , QSize{ kDiamter, kDiamter } };
            if (itOfPieces != pieces_.end()) {
                painter.drawPixmap(rect, itOfPieces->pixmap());
                ++itOfPieces;
            } else {
                painter.drawEllipse(rect);
            }
        }
    }
}

void GainFrame::addPiece(Piece piece)
{
    if (piece.bi() == flag_) {
        pieces_.push_back(std::move(piece));
        update();
    }
}
