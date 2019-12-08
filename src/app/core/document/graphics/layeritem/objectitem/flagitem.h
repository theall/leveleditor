#ifndef TFLAGITEM_H
#define TFLAGITEM_H

#include "pointobjectitem.h"

class TPointObject;
class TFlagItem : public TPointObjectItem
{
    Q_OBJECT

public:
    TFlagItem(TPointObject *pointObject, QGraphicsItem *parent = Q_NULLPTR);

    QColor color() const;
    void setColor(const QColor &color);

private:
    QColor mColor;

    // QGraphicsItem interface
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // TObjectItem interface
public:
    void propertyValueChanged(PropertyID pid);
};

#endif // TFLAGITEM_H
