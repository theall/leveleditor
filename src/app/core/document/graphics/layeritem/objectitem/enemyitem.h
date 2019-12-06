#ifndef TENEMYITEM_H
#define TENEMYITEM_H

#include "objectitem.h"
#include "../../../model/entity/enemy.h"

class TEnemyItem : public TObjectItem
{
    Q_OBJECT

public:
    explicit TEnemyItem(TEnemy *enemy, QGraphicsItem *parent = Q_NULLPTR);
    ~TEnemyItem();

    TEnemy *enemy() const;

private:
    TEnemy *mEnemy;

    // TObjectItem interface
public:
    void propertyValueChanged(PropertyID pid) Q_DECL_OVERRIDE;

    // QGraphicsItem interface
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
typedef QList<TEnemyItem*> TEnemyItemList;

#endif // TENEMYITEM_H
