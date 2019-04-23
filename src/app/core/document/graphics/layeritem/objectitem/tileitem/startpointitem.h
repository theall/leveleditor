#ifndef TSTARTPOINTITEM_H
#define TSTARTPOINTITEM_H

#include "../objectitem.h"

class TDoorItem;
class TStartPoint;
class TStartPointItem : public TObjectItem
{
public:
    TStartPointItem(TDoorItem *doorItem);
    ~TStartPointItem();

private:
    TStartPoint *mStartPoint;

    void updateBoundingRect();

    // QGraphicsItem interface
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    // TObjectItem interface
public:
    void propertyValueChanged(PropertyID pid) Q_DECL_OVERRIDE;
};
#endif // TSTARTPOINTITEM_H
