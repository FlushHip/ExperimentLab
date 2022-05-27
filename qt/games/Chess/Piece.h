#pragma once

#include <QPixmap>

#include <map>

enum class PieceBi : char {
    kRed,
    kBlack,
};

enum class PieceType : char {
    kG,
    kA,
    kE,
    kH,
    kR,
    kC,
    kS,
};

using Point = std::pair<int, int>;

class Piece {
public:
    Piece() = default;
    Piece(PieceBi bi, PieceType type)
        : bi_(bi), type_(type), choosed_(false) {}

    PieceBi bi() const { return bi_; };
    PieceType type() const { return type_; };
    bool choosed() const { return choosed_; };
    void setChoosed(bool choosed = false) { choosed_ = choosed; };
    const QPixmap & pixmap() const { return GetPieceToPixmapMap()[{ type_, bi_ }]; };

    void draw(const Point &point, QPainter &painter);

    static std::map<Point, Piece> GetInitStatusPieces();

private:
    static std::map<std::pair<PieceType, PieceBi>, QPixmap>& GetPieceToPixmapMap();

    PieceBi bi_;
    PieceType type_;

    bool choosed_;
};
