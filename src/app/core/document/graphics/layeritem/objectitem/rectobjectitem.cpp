#include "rectobjectitem.h"

TRectObjectItem::TRectObjectItem(TRectObject *rectObject, QGraphicsItem *parent) :
    TObjectItem(rectObject, parent)
{
    setBoundingRect(rectObject->getRect());
}
