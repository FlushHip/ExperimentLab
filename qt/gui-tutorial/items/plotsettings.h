#pragma once

class PlotSettings
{
public:
    PlotSettings();

    void scroll(int dx, int dy);
    void adjust();
    double spanX() const { return maxX - minX; };
    double spanY() const { return maxY - minY; };

public:
    double minX, maxX;
    double minY, maxY;
    int numXTicks, numYTicks;

private:
    static void adjustAxis(double &min, double &max, int &numTicks);
};
