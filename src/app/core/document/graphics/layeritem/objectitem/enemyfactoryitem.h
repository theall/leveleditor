#ifndef TENEMYFACTORYITEM_H
#define TENEMYFACTORYITEM_H

#include "objectitem.h"
#include "enemyitem.h"

class TEnemyFactory;
class TEnemyFactoryItem : public TObjectItem
{
public:
    explicit TEnemyFactoryItem(TEnemyFactory *enemyFactory, QGraphicsItem *parent = Q_NULLPTR);
    ~TEnemyFactoryItem();

private:
    TEnemyItemList mEnemyItemList;

    // TObjectItem interface
public:
    void propertyValueChanged(PropertyID pid);
};
typedef QList<TEnemyFactoryItem*> TEnemyFactoryItemList;

#endif // TENEMYFACTORYITEM_H
