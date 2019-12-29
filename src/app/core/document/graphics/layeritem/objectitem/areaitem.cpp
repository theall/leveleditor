#include "areaitem.h"
#include "platitem.h"

#include <QPainter>

TAreaItem::TAreaItem(TArea *area, QGraphicsItem *parent) :
    TRectObjectItem(area, parent)
  , mArea(area)
{
    Q_ASSERT(mArea);
    setBorderColor(Qt::green);
}

TAreaItem::~TAreaItem()
{

}

TArea *TAreaItem::area() const
{
    return mArea;
}

QRectF TAreaItem::getIndicatorRect(const QRectF &rect)
{
    QRectF indicatorRect(-5,-5,11,11);
    indicatorRect.moveCenter(rect.center());
    return indicatorRect;
}

void TAreaItem::propertyValueChanged(PropertyID)
{

}

void TAreaItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    TRectObjectItem::paint(painter, option, widget);
    TPlat *plat = mArea->plat();
    QRectF areaRect = mArea->getRect();
    QRectF indicatorStartRect = getIndicatorRect(areaRect);
    painter->fillRect(indicatorStartRect, Qt::white);
    if(!plat) {
        return;
    }
    TPlatItem *platItem = (TPlatItem*)TObjectItem::getObjectItem(plat);
    if(!platItem)
        return;
    QRectF indicatorToRect = getIndicatorRect(platItem->boundingRect());
    painter->fillRect(indicatorToRect, Qt::black);

    painter->setPen(Qt::DashLine);
    painter->drawLine(indicatorStartRect.center(), indicatorToRect.center());
}
