#include "spreadsheet_compare.h"

bool SpreadsheetCompare::operator()(const QStringList &row1, const QStringList &row2) const
{
    for (int i = 0; i < KeyCount; ++i) {
        int column = keys[i];
        if (column == -1) {
            continue;
        }
        if (row1[column] != row2[column]) {
            return ascending[i] ? row1[column] < row2[column] : row1[column] > row2[column];
        }
    }
    return false;
}
