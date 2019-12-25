#ifndef TBOXITEM_H
#define TBOXITEM_H

#include "rectobjectitem.h"
#include "../../../model/entity/box.h"

class TBoxItem : public TRectObjectItem
{
    Q_OBJECT

public:
    TBoxItem(TBox *box, QGraphicsItem *parent = Q_NULLPTR);
    ~TBoxItem();

    TBox *box() const;

private:
    TBox *mBox;

    // TObjectItem interface
public:
    void propertyValueChanged(PropertyID pid) Q_DECL_OVERRIDE;

    // QGraphicsItem interface
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
typedef QList<TBoxItem*> TBoxItemList;

#endif // TBOXITEM_H
