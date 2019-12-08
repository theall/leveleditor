#ifndef TPLAYERITEM_H
#define TPLAYERITEM_H

#include "pointobjectitem.h"
#include "../../../model/entity/pointobject.h"

#include <QColor>

class TPlayerItem : public TPointObjectItem
{
public:
    TPlayerItem(TPointObject *pointObject, QGraphicsItem *parent = Q_NULLPTR);
    ~TPlayerItem();

    QColor getColor() const;
    void setColor(const QColor &color);

private:
    QColor mColor;

public:
    void propertyValueChanged(PropertyID pid) Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
};

#endif // TPLAYERITEM_H
