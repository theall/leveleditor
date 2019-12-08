#include "triggeritem.h"

TTriggerItem::TTriggerItem(TTrigger *trigger, QGraphicsItem *parent) :
    TRectObjectItem(trigger, parent)
{

}

TTrigger *TTriggerItem::trigger() const
{
    return mTrigger;
}

void TTriggerItem::setTrigger(TTrigger *trigger)
{
    mTrigger = trigger;
}

void TTriggerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

}

void TTriggerItem::propertyValueChanged(PropertyID)
{

}
