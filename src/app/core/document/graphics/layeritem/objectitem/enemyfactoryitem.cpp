#include "enemyfactoryitem.h"
#include "../../../model/entity/enemyfactory.h"

TEnemyFactoryItem::TEnemyFactoryItem(TEnemyFactory *enemyFactory, QGraphicsItem *parent) :
    TObjectItem(enemyFactory, parent)
{
    Q_ASSERT(enemyFactory);

    for(TEnemy *enemy : enemyFactory->enemyList()) {
        TEnemyItem *enemyItem = new TEnemyItem(enemy, parent);
        mEnemyItemList.append(enemyItem);
    }
}

TEnemyFactoryItem::~TEnemyFactoryItem()
{

}

void TEnemyFactoryItem::propertyValueChanged(PropertyID)
{

}
