#pragma once

#include <QFrame>

#include "Piece.h"

class GainFrame : QFrame
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
    PieceBi flag_;
    std::vector<Piece> pieces_;
};
