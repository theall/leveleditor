#include "rectobjectitem.h"

TRectObjectItem::TRectObjectItem(TRectObject *rectObject, QGraphicsItem *parent) :
    TObjectItem(rectObject, parent)
{
    setCurrentPos(rectObject->getPos());
    setBoundingRect(rectObject->getRect());
}
