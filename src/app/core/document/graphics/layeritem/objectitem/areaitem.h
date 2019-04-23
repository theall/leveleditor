#ifndef TAREAITEM_H
#define TAREAITEM_H

#include "objectitem.h"
#include "../../../model/entity/area.h"

class TAreaItem : public TObjectItem
{
    Q_OBJECT

public:
    TAreaItem(TArea *area, QGraphicsItem *parent = Q_NULLPTR);
    ~TAreaItem();

    TArea *area() const;
    void setArea(TArea *area);

    QColor color() const;
    void setColor(const QColor &color);

private:
    TArea *mArea;
    QColor mColor;

    // QGraphicsItem interface
public:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;

    // TObjectItem interface
public:
    void propertyValueChanged(PropertyID pid) Q_DECL_OVERRIDE;
};
typedef QList<TAreaItem*> TAreaItemList;

#endif // TAREAITEM_H
