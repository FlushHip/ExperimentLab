#include "plotter.h"

#include <QToolButton>
#include <QStylePainter>
#include <QStyleOptionFocusRect>
#include <QMouseEvent>

#include "items/plotsettings.h"

Plotter::Plotter(QWidget *parent)
    : QWidget(parent)
{
    setBackgroundRole(QPalette::Dark);
    setAutoFillBackground(true);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setFocusPolicy(Qt::StrongFocus);

    rubberBandIsShown_ = false;

    zoomInButton_ = new QToolButton(this);
    zoomInButton_->setIcon(QIcon(":/images/zoomin.png"));
    zoomInButton_->adjustSize();
    connect(zoomInButton_, &QToolButton::clicked, this, &Plotter::zoomIn);

    zoomOutButton_ = new QToolButton(this);
    zoomOutButton_->setIcon(QIcon(":/images/zoomout.png"));
    zoomOutButton_->adjustSize();
    connect(zoomOutButton_, &QToolButton::clicked, this, &Plotter::zoomIn);

    setPlotSettings(PlotSettings{});
}

Plotter::~Plotter() = default;

void Plotter::setPlotSettings(const PlotSettings &settings)
{
    zoomStack_.clear();
    zoomStack_.append(settings);
    curZoom_ = 0;
    zoomInButton_->hide();
    zoomOutButton_->hide();
    refreshPixmap();
}

void Plotter::zoomOut()
{
    if (curZoom_ > 0) {
        --curZoom_;
        zoomOutButton_->setEnabled(curZoom_ > 0);
        zoomInButton_->setEnabled(true);
        zoomInButton_->show();

        refreshPixmap();
    }
}

void Plotter::zoomIn()
{
    if (curZoom_ < zoomStack_.count() - 1) {
        --curZoom_;
        zoomInButton_->setEnabled(curZoom_ < zoomStack_.count() - 1);
        zoomOutButton_->setEnabled(true);
        zoomOutButton_->show();

        refreshPixmap();
    }
}

void Plotter::setCurveData(int id, const QVector<QPointF> &data)
{
    curveMap_[id] = data;
    refreshPixmap();
}

void Plotter::clearCurve(int id)
{
    curveMap_.remove(id);
    refreshPixmap();
}

QSize Plotter::minimumSizeHint() const
{
    return QSize(6 * Margin, 4 * Margin);
}

QSize Plotter::sizeHint() const
{
    return QSize(12 * Margin, 8 * Margin);
}

void Plotter::paintEvent(QPaintEvent *event)
{
    QStylePainter painter(this);
    painter.drawPixmap(0, 0, pixmap_);

    if (rubberBandIsShown_) {
        painter.setPen(palette().light().color());
        painter.drawRect(rubberBandRect_.normalized());
    }

    if (hasFocus()) {
        QStyleOptionFocusRect option;
        option.initFrom(this);
        option.backgroundColor = palette().dark().color();
        painter.drawPrimitive(QStyle::PE_FrameFocusRect, option);
    }
}

void Plotter::resizeEvent(QResizeEvent *event)
{
    int x = width() - (zoomInButton_->width() + zoomOutButton_->width() + 5 + 5);
    zoomInButton_->move(x, 5);
    zoomOutButton_->move(x + zoomInButton_->width() + 5, 5);

    refreshPixmap();
}

void Plotter::mousePressEvent(QMouseEvent *event)
{
    QRect rect(Margin, Margin, width() - 2 * Margin, height() - 2 * Margin);
    if (event->button() == Qt::LeftButton
        && rect.contains(event->pos())) {
        rubberBandIsShown_ = true;
        rubberBandRect_.setTopLeft(event->pos());
        rubberBandRect_.setBottomRight(event->pos());
        updateRubberBandRegion();
        setCursor(Qt::CrossCursor);
    }
}

void Plotter::mouseMoveEvent(QMouseEvent *event)
{
    if (rubberBandIsShown_) {
        updateRubberBandRegion();
        rubberBandRect_.setBottomRight(event->pos());
        updateRubberBandRegion();
    }
}

void Plotter::mouseReleaseEvent(QMouseEvent *event)
{
    if (rubberBandIsShown_ && event->button() == Qt::LeftButton) {
        rubberBandIsShown_ = false;
        updateRubberBandRegion();
        unsetCursor();

        QRect rect = rubberBandRect_.normalized();
        if (rect.width() < 4 || rect.height() < 4) {
            return ;
        }
        rect.translate(-Margin, -Margin);

        PlotSettings prevSettings = zoomStack_[curZoom_];
        PlotSettings settings;
    }
}
