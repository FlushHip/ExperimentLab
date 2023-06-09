#pragma once

#include <QMap>
#include <QPointF>
#include <QVector>
#include <QWidget>

class QToolButton;

class PlotSettings;

class Plotter : public QWidget {
    Q_OBJECT
public:
    Plotter(QWidget* parent = Q_NULLPTR);
    ~Plotter() override;

    void setPlotSettings(const PlotSettings& settings);
    void setCurveData(int id, const QVector<QPointF>& data);
    void clearCurve(int id);
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

public slots:
    void zoomIn();
    void zoomOut();

protected:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    // void wheelEvent(QWheelEvent *event) override;
    // void keyPressEvent(QKeyEvent* event) override;

private:
    void updateRubberBandRegion();
    void refreshPixmap();
    void drawGrid(QPainter* painter);
    void drawCurves(QPainter* painter);

private:
    enum { Margin = 50 };

    QToolButton* zoomInButton_;
    QToolButton* zoomOutButton_;
    QMap<int, QVector<QPointF>> curveMap_;
    QVector<PlotSettings> zoomStack_;
    int curZoom_;
    bool rubberBandIsShown_;
    QRect rubberBandRect_;
    QPixmap pixmap_;
};
