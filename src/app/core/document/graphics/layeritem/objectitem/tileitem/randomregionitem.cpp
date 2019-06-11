#include "randomregionitem.h"
#include "dooritem.h"

TRandomRegionItem::TRandomRegionItem(TDoorItem *doorItem) :
    TObjectItem(nullptr, doorItem)
{

}

QRectF TRandomRegionItem::boundingRect() const
{
    return QRectF();
}

void TRandomRegionItem::paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *)
{

}

void TRandomRegionItem::propertyValueChanged(PropertyID)
{

}
