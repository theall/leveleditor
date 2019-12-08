#include "pointobjectitem.h"

TPointObjectItem::TPointObjectItem(TPointObject *pointRect, QGraphicsItem *parent) :
    TObjectItem(pointRect, parent)
{
    setAnchor(TObjectItem::BOTTOM_CENTER);
}
