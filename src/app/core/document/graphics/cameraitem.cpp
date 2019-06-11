#include "cameraitem.h"

#include <QPen>
#include <QPainter>

TCameraItem::TCameraItem(QGraphicsItem *parent) :
    QGraphicsObject(parent)
  , mBorderColor(QColor(Qt::white))
  , mBoundingRect(QRectF(QPointF(),QSize(400,400)))
  , mIcon(new QPixmap(":/scenemodel/images/camera.png"))
{

}

TCameraItem::~TCameraItem()
{

}

void TCameraItem::setBoundingRect(const QRectF &boundingRect)
{
    if(mBoundingRect == boundingRect)
        return;

    prepareGeometryChange();
    mBoundingRect = boundingRect;
}

QColor TCameraItem::borderColor() const
{
    return mBorderColor;
}

void TCameraItem::setBorderColor(const QColor &borderColor)
{
    mBorderColor = borderColor;
}

QRectF TCameraItem::boundingRect() const
{
    return mBoundingRect;
}

void TCameraItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPen pen(mBorderColor);
    pen.setStyle(Qt::SolidLine);
    painter->setPen(pen);
    painter->drawRect(mBoundingRect);

    painter->drawPixmap(mBoundingRect.x()+10, mBoundingRect.y()+10, *mIcon);
}
