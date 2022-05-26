#include "Piece.h"

#include <QPainter>

#include "common_define.h"

std::map<std::pair<PieceType, PieceBi>, QPixmap>& Piece::GetPieceToPixmapMap()
{
    static std::map<std::pair<PieceType, PieceBi>, QPixmap> sPieceToPixmapMap = {
        { {PieceType::kG, PieceBi::kBlack}, QPixmap(":/piece/gd") },
        { {PieceType::kG, PieceBi::kRed}, QPixmap(":/piece/gl") },
        { {PieceType::kA, PieceBi::kBlack}, QPixmap(":/piece/ad") },
        { {PieceType::kA, PieceBi::kRed}, QPixmap(":/piece/al") },
        { {PieceType::kE, PieceBi::kBlack}, QPixmap(":/piece/ed") },
        { {PieceType::kE, PieceBi::kRed}, QPixmap(":/piece/el") },
        { {PieceType::kH, PieceBi::kBlack}, QPixmap(":/piece/hd") },
        { {PieceType::kH, PieceBi::kRed}, QPixmap(":/piece/hl") },
        { {PieceType::kR, PieceBi::kBlack}, QPixmap(":/piece/rd") },
        { {PieceType::kR, PieceBi::kRed}, QPixmap(":/piece/rl") },
        { {PieceType::kC, PieceBi::kBlack}, QPixmap(":/piece/cd") },
        { {PieceType::kC, PieceBi::kRed}, QPixmap(":/piece/cl") },
        { {PieceType::kS, PieceBi::kBlack}, QPixmap(":/piece/sd") },
        { {PieceType::kS, PieceBi::kRed}, QPixmap(":/piece/sl") },
    };
    return sPieceToPixmapMap;
}

std::map<Point, Piece> Piece::GetInitStatusPieces()
{
    static std::map<Point, Piece> sPieces {
        { { 0, 0 }, { PieceBi::kBlack, PieceType::kR } },
        { { 1, 0 }, { PieceBi::kBlack, PieceType::kH } },
        { { 2, 0 }, { PieceBi::kBlack, PieceType::kE } },
        { { 3, 0 }, { PieceBi::kBlack, PieceType::kA } },
        { { 4, 0 }, { PieceBi::kBlack, PieceType::kG } },
        { { 5, 0 }, { PieceBi::kBlack, PieceType::kA } },
        { { 6, 0 }, { PieceBi::kBlack, PieceType::kE } },
        { { 7, 0 }, { PieceBi::kBlack, PieceType::kH } },
        { { 8, 0 }, { PieceBi::kBlack, PieceType::kR } },
        { { 1, 2 }, { PieceBi::kBlack, PieceType::kC } },
        { { 7, 2 }, { PieceBi::kBlack, PieceType::kC } },
        { { 0, 3 }, { PieceBi::kBlack, PieceType::kS } },
        { { 2, 3 }, { PieceBi::kBlack, PieceType::kS } },
        { { 4, 3 }, { PieceBi::kBlack, PieceType::kS } },
        { { 6, 3 }, { PieceBi::kBlack, PieceType::kS } },
        { { 8, 3 }, { PieceBi::kBlack, PieceType::kS } },

        { { 0, 9 }, { PieceBi::kRed, PieceType::kR } },
        { { 1, 9 }, { PieceBi::kRed, PieceType::kH } },
        { { 2, 9 }, { PieceBi::kRed, PieceType::kE } },
        { { 3, 9 }, { PieceBi::kRed, PieceType::kA } },
        { { 4, 9 }, { PieceBi::kRed, PieceType::kG } },
        { { 5, 9 }, { PieceBi::kRed, PieceType::kA } },
        { { 6, 9 }, { PieceBi::kRed, PieceType::kE } },
        { { 7, 9 }, { PieceBi::kRed, PieceType::kH } },
        { { 8, 9 }, { PieceBi::kRed, PieceType::kR } },
        { { 1, 7 }, { PieceBi::kRed, PieceType::kC } },
        { { 7, 7 }, { PieceBi::kRed, PieceType::kC } },
        { { 0, 6 }, { PieceBi::kRed, PieceType::kS } },
        { { 2, 6 }, { PieceBi::kRed, PieceType::kS } },
        { { 4, 6 }, { PieceBi::kRed, PieceType::kS } },
        { { 6, 6 }, { PieceBi::kRed, PieceType::kS } },
        { { 8, 6 }, { PieceBi::kRed, PieceType::kS } },
    };
    return sPieces;
}

void Piece::draw(const Point &point, QPainter &painter)
{
    painter.drawPixmap(point.first * kUnitLength, point.second * kUnitLength, pixmap());
}
