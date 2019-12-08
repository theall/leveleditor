#include "flagitem.h"
#include "../../../model/entity/pointobject.h"
#include "../../../property/propertyitem.h"

#include <QPainter>

#define FLAG_HEIGHT 24
#define FLAG_WIDTH  10
#define STICKY_WIDTH 4
#define BOUNDING_WIDTH 16

TFlagItem::TFlagItem(TPointObject *pointObject, QGraphicsItem *parent) :
    TPointObjectItem(pointObject, parent)
  , mColor(Qt::green)
{
    Q_ASSERT(pointObject);

    setBoundingRect(QRectF(-BOUNDING_WIDTH/2,-FLAG_HEIGHT,BOUNDING_WIDTH,FLAG_HEIGHT));
    move(pointObject->pos());
}

QColor TFlagItem::color() const
{
    return mColor;
}

void TFlagItem::setColor(const QColor &color)
{
    mColor = color;
}

void TFlagItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPointF currentPos = getCurrentPos();
    float x = currentPos.x();
    float y = currentPos.y();
    QRectF stickyRect(x-BOUNDING_WIDTH/2, y-FLAG_HEIGHT, STICKY_WIDTH, FLAG_HEIGHT);
    QRectF flagRect(x-BOUNDING_WIDTH/2+STICKY_WIDTH, y+2-FLAG_HEIGHT, FLAG_WIDTH, FLAG_WIDTH);
    painter->fillRect(stickyRect, Qt::white);
    painter->fillRect(flagRect, mColor);
}

void TFlagItem::propertyValueChanged(PropertyID)
{

}
