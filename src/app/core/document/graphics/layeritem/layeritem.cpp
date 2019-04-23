#include "layeritem.h"

TLayerItem::TLayerItem(QGraphicsItem *parent) :
    QGraphicsObject(parent)
{

}

QRectF TLayerItem::boundingRect() const
{
    return mBoundingRect;
}

void TLayerItem::paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *)
{

}
