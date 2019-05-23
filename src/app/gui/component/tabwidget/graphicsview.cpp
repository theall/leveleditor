#include "graphicsview.h"

TGraphicsView::TGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
  , mLeftButtonDown(false)
{

}

TGraphicsView::~TGraphicsView()
{

}

qreal TGraphicsView::scale() const
{
    return mScale;
}

void TGraphicsView::setScale(const qreal &scale)
{
    if(mScale == scale)
        return;

    mScale = scale;
    setTransform(QTransform::fromScale(mScale, mScale));
}

void TGraphicsView::resizeEvent(QResizeEvent *)
{
    emit resized();
}

void TGraphicsView::contextMenuEvent(QContextMenuEvent *event)
{
    emit requestPopupContextMenu(event->globalPos());
}

void TGraphicsView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);

    mLeftButtonDown = true;
}

void TGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);

    mLeftButtonDown = false;
}

void TGraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
{
    QGraphicsView::mouseDoubleClickEvent(event);
}

void TGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);

    if(!mLeftButtonDown)
        return;

    QGraphicsScene *graphicsScene = scene();
    if(!graphicsScene)
        return;

    if(!viewport()->geometry().contains(event->pos()))
        centerOn(event->pos());
}
