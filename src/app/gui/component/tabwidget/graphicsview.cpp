#include "graphicsview.h"

TGraphicsView::TGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
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
