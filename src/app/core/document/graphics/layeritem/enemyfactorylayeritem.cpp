#include "enemyfactorylayeritem.h"

#include "../../model/enemyfactorymodel.h"

TEnemyFactoryLayerItem::TEnemyFactoryLayerItem(TEnemyFactoryModel *enemyFactoryModel, QGraphicsItem *parent) :
    TObjectLayerItem(enemyFactoryModel, parent)
{
    Q_ASSERT(enemyFactoryModel);

    for(TEnemyFactory *enemyFactory : enemyFactoryModel->enemyFactoryList()) {
        TEnemyFactoryItem *enemyFactoryItem = new TEnemyFactoryItem(enemyFactory, this);
        mEnemyFactoryList.append(enemyFactoryItem);
    }

    calcBoundingRect();
}

TEnemyFactoryLayerItem::~TEnemyFactoryLayerItem()
{

}
