#ifndef TBOXITEM_H
#define TBOXITEM_H

#include "objectitem.h"
#include "../../../model/entity/box.h"

class TBoxItem : public TObjectItem
{
    Q_OBJECT

public:
    TBoxItem(TBox *box, QGraphicsItem *parent = Q_NULLPTR);
    ~TBoxItem();

    TBox *box() const;
    void setBox(TBox *box);

    QColor color() const;
    void setColor(const QColor &color);

private:
    TBox *mBox;
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
typedef QList<TBoxItem*> TBoxItemList;

#endif // TBOXITEM_H
