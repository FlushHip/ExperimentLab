#include "headers.h"

class Solution {
public:
    bool checkOverlap(int radius,
        int xCenter,
        int yCenter,
        int x1,
        int y1,
        int x2,
        int y2) {
        int x_lhs = std::max(x1, xCenter - radius),
            x_rhs = std::min(x2, xCenter + radius),
            y_lhs = std::max(y1, yCenter - radius),
            y_rhs = std::min(y2, yCenter + radius);
        for (int x = x_lhs; x <= x_rhs; ++x) {
            for (int y = y_lhs; y <= y_rhs; ++y) {
                if ((x - xCenter) * (x - xCenter) +
                            (y - yCenter) * (y - yCenter) <=
                        radius * radius &&
                    x1 <= x && x <= x2 && y1 <= y && y <= y2) {
                    return true;
                }
            }
        }
        return false;
    }
};
