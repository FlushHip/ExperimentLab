#pragma once

#include <QFrame>

#include "Piece.h"
#include "common_define.h"

class GainFrame : public QFrame
{
    Q_OBJECT
public:
    explicit GainFrame(PieceBi flag, QWidget *parent = nullptr);
    ~GainFrame() override;

protected:
    void paintEvent(QPaintEvent *) override;

public slots:
    void addPiece(Piece piece);

private:
    static const int kDiamter = kUnitLength - 10;
    PieceBi flag_;
    std::vector<Piece> pieces_;
};
