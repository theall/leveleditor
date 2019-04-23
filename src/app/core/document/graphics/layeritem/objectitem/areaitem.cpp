#include "areaitem.h"
#include <QPainter>

TAreaItem::TAreaItem(TArea *area, QGraphicsItem *parent) :
    TObjectItem(area, parent)
  , mArea(area)
  , mColor(Qt::red)
{
    Q_ASSERT(mArea);
}

TAreaItem::~TAreaItem()
{

}

TArea *TAreaItem::area() const
{
    return mArea;
}

void TAreaItem::setArea(TArea *area)
{
    mArea = area;
}

QColor TAreaItem::color() const
{
    return mColor;
}

void TAreaItem::setColor(const QColor &color)
{
    mColor = color;
}

QRectF TAreaItem::boundingRect() const
{
    return mArea->rect();
}

void TAreaItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPen pen(mColor);
    painter->setPen(pen);
    painter->drawRect(mArea->rect());
}

QPainterPath TAreaItem::shape() const
{
    QPainterPath p;
    p.addRect(mArea->rect());
    return p;
}

void TAreaItem::propertyValueChanged(PropertyID pid)
{
    // Notify to selection item or hovering item
    if(pid==PID_AREA_RECT) {
        emit boundingRectChanged();
    }
}
