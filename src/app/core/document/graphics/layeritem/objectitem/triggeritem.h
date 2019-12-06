#ifndef TTRIGGERITEM_H
#define TTRIGGERITEM_H

#include "objectitem.h"
#include "../../../model/entity/trigger.h"

class TTriggerItem : public TObjectItem
{
public:
    TTriggerItem(TTrigger *trigger, QGraphicsItem *parent = Q_NULLPTR);

    TTrigger *trigger() const;
    void setTrigger(TTrigger *trigger);

private:
    TTrigger *mTrigger;

    // QGraphicsItem interface
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // TObjectItem interface
public:
    void propertyValueChanged(PropertyID pid);
};
typedef QList<TTriggerItem*> TTriggerItemList;

#endif // TTRIGGERITEM_H
