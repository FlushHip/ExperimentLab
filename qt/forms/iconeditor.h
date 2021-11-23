#pragma once

#include <QWidget>
#include <QImage>
#include <QColor>

class IconEditor : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor)
    Q_PROPERTY(QImage iconImage READ iconImage WRITE setIconImage)
    Q_PROPERTY(int zoomFactor READ zoomFactor WRITE setZoomFactor)
public:
    IconEditor(QWidget *parent = Q_NULLPTR);
    ~IconEditor() override;

    QColor penColor() const { return curColor_; };
    void setPenColor(const QColor &color);
    QImage iconImage() const { return image_; };
    void setIconImage(const QImage &image);
    int zoomFactor() const { return zoom_; };
    void setZoomFactor(int zoom);

    QSize sizeHint() const;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void setImagePixel(const QPoint &pos, bool opaque);
    QRect pixelRect(int i, int j) const;

private:
    QColor curColor_;
    QImage image_;
    int zoom_;
};
