#ifndef TRANDOMREGIONITEM_H
#define TRANDOMREGIONITEM_H

#include "../objectitem.h"

class TDoorItem;
class TRandomRegionItem : public TObjectItem
{
public:
    TRandomRegionItem(TDoorItem *doorItem);

private:

    // QGraphicsItem interface
public:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    // TObjectItem interface
public:
    void propertyValueChanged(PropertyID pid) Q_DECL_OVERRIDE;
};

#endif // TRANDOMREGIONITEM_H
