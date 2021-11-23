#include "iconeditor.h"

#include <QPainter>
#include <QPaintEvent>

IconEditor::IconEditor(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    curColor_ = Qt::black;
    zoom_ = 16;
    image_ = QImage(16, 16, QImage::Format_ARGB32);
    image_.fill(qRgba(0, 0, 0, 0));
}

IconEditor::~IconEditor() = default;

QSize IconEditor::sizeHint() const
{
    QSize size = zoom_ * image_.size();
    if (zoom_ >= 3) {
        size += QSize(1, 1);
    }
    return size;
}

void IconEditor::setPenColor(const QColor &color)
{
    curColor_ = color;
}

void IconEditor::setIconImage(const QImage &image)
{
    if (image_ == image) {
        return ;
    }
    image_ = image.convertToFormat(QImage::Format_ARGB32);
    update();
    updateGeometry();
}

void IconEditor::setZoomFactor(int zoom)
{
    if (zoom < 1) {
        zoom = 1;
    }
    if (zoom_ != zoom) {
        zoom_ = zoom;
        update();
        updateGeometry();
    }
}

void IconEditor::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if (zoom_ >= 3) {
        painter.setPen(palette().windowText().color());
        for (int i = 0; i < image_.width() + 1; ++i) {
            painter.drawLine(i * zoom_, 0, i * zoom_, image_.height() * zoom_);
        }
        for (int i = 0; i < image_.height() + 1; ++i) {
            painter.drawLine(0, i * zoom_, image_.width() * zoom_, i * zoom_);
        }
    }

    for (int i = 0; i < image_.width(); ++i) {
        for (int j = 0; j < image_.height(); ++j) {
            QRect rect = pixelRect(i, j);
            if (!event->region().intersected(rect).isEmpty()) {
                QColor color = QColor::fromRgba(image_.pixel(i, j));
                if (color.alpha() < 255) {
                    painter.fillRect(rect, Qt::white);
                }
                painter.fillRect(rect, color);
            }
        }
    }
}

QRect IconEditor::pixelRect(int i, int j) const
{
    if (zoom_ >= 3) {
        return QRect(i * zoom_ + 1, j * zoom_ + 1, zoom_ - 1, zoom_ - 1);
    }
    return QRect(i * zoom_, j * zoom_, zoom_, zoom_);
}

void IconEditor::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        setImagePixel(event->pos(), true);
    } else if (event->button() == Qt::RightButton) {
        setImagePixel(event->pos(), false);
    }
}

void IconEditor::mouseMoveEvent(QMouseEvent *event)
{
    if (event->button() & Qt::LeftButton) {
        setImagePixel(event->pos(), true);
    } else if (event->button() & Qt::RightButton) {
        setImagePixel(event->pos(), false);
    }
}

void IconEditor::setImagePixel(const QPoint &pos, bool opaque)
{
    int i = pos.x() / zoom_;
    int j = pos.y() / zoom_;

    if (image_.rect().contains(i, j)) {
        if (opaque) {
            image_.setPixel(i, j, penColor().rgba());
        } else {
            image_.setPixel(i, j, qRgba(0, 0, 0, 0));
        }

        update(pixelRect(i, j));
    }
}
