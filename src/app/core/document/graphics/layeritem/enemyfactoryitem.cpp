#include "enemyfactoryitem.h"
#include "objectitem/wallitem.h"
#include "../../model/enemyfactorymodel.h"

TEnemyFactoryItem::TEnemyFactoryItem(TEnemyFactoryModel *enemyFactoryModel, QGraphicsItem *parent) :
    TObjectLayerItem(enemyFactoryModel, parent)
{
    Q_ASSERT(enemyFactoryModel);

    for(TEnemyFactory *enemyFactory : enemyFactoryModel->enemyFactoryList()) {

    }

    calcBoundingRect();
}

TEnemyFactoryItem::~TEnemyFactoryItem()
{

}
