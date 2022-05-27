#include "GainFrame.h"

GainFrame::GainFrame(PieceBi flag, QWidget *parent)
    : flag_(flag)
    , QFrame(parent)
{
    setParent(parent);

    //setFixedSize({  })
}

GainFrame::~GainFrame() = default;


void GainFrame::paintEvent(QPaintEvent *)
{

}

void GainFrame::addPiece(Piece piece)
{
    if (piece.bi() == flag_) {
        pieces_.push_back(std::move(piece));
        update();
    }
}
