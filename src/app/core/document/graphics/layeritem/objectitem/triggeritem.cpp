#include "triggeritem.h"
#include "../../../model/entity/trigger.h"
#include "../../../../assets/triggerid.h"

#include <QPainter>

TTriggerItem::TTriggerItem(TTrigger *trigger, QGraphicsItem *parent) :
    TRectObjectItem(trigger, parent)
  , mTrigger(trigger)
{
    Q_ASSERT(trigger);

    setBorderColor(Qt::magenta);
}

TTrigger *TTriggerItem::trigger() const
{
    return mTrigger;
}

void TTriggerItem::setTrigger(TTrigger *trigger)
{
    mTrigger = trigger;
}

void TTriggerItem::propertyValueChanged(PropertyID)
{

}

void TTriggerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    TTriggerId *triggerId = mTrigger->triggerId();
    if(triggerId) {
        QPointF imageOffset = mTrigger->getImageOffset();
        QPixmap pixmap = triggerId->onPixmap()->content();
        imageOffset += QPointF(pixmap.width()/2, -pixmap.height());
        painter->drawPixmap(mCurrentPos+imageOffset, pixmap);
    }
    TRectObjectItem::paint(painter, option, widget);
}
