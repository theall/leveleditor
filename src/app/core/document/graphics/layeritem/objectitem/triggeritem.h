#ifndef TTRIGGERITEM_H
#define TTRIGGERITEM_H

#include "rectobjectitem.h"

class TTrigger;
class TTriggerItem : public TRectObjectItem
{
public:
    TTriggerItem(TTrigger *trigger, QGraphicsItem *parent = Q_NULLPTR);

    TTrigger *trigger() const;
    void setTrigger(TTrigger *trigger);

private:
    TTrigger *mTrigger;

    // TObjectItem interface
public:
    void propertyValueChanged(PropertyID pid);

    // QGraphicsItem interface
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
typedef QList<TTriggerItem*> TTriggerItemList;

#endif // TTRIGGERITEM_H
