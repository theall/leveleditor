#ifndef TAREAITEM_H
#define TAREAITEM_H

#include "rectobjectitem.h"
#include "../../../model/entity/area.h"

class TAreaItem : public TRectObjectItem
{
    Q_OBJECT

public:
    TAreaItem(TArea *area, QGraphicsItem *parent = Q_NULLPTR);
    ~TAreaItem();

    TArea *area() const;

private:
    TArea *mArea;
    QRectF getIndicatorRect(const QRectF &rect);

    // TObjectItem interface
public:
    void propertyValueChanged(PropertyID pid) Q_DECL_OVERRIDE;

    // QGraphicsItem interface
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
typedef QList<TAreaItem*> TAreaItemList;

#endif // TAREAITEM_H
