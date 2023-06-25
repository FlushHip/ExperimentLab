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
        int x = std::clamp(xCenter, x1, x2), y = std::clamp(yCenter, y1, y2);
        return (x - xCenter) * (x - xCenter) + (y - yCenter) * (y - yCenter) <=
            radius * radius;
    }
};
