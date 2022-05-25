#pragma once

#include <QStringList>

class SpreadsheetCompare
{
public:
    bool operator()(const QStringList &row1, const QStringList &row2) const;
    enum { KeyCount = 3 };

    int keys[KeyCount];
    bool ascending[KeyCount];
};
