#include "triggeritem.h"

TTriggerItem::TTriggerItem(TTrigger *trigger, QGraphicsItem *parent) :
    TObjectItem(trigger, parent)
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

void TTriggerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

void TTriggerItem::propertyValueChanged(PropertyID pid)
{

}
