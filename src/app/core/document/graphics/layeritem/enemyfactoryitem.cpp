#include "enemyfactoryitem.h"
#include "objectitem/wallitem.h"
#include "../../model/enemyfactorymodel.h"

TEnemyFactoryItem::TEnemyFactoryItem(TEnemyFactoryModel *enemyFactoryModel, QGraphicsItem *parent) :
    TObjectLayerItem(enemyFactoryModel, parent)
{
    Q_ASSERT(enemyFactoryModel);

    for(TWall *wall : enemyFactoryModel.()) {
        TWallItem *wallItem = new TWallItem(wall, this);
        mObjectItemList.append(wallItem);
    }

    calcBoundingRect();
}

TEnemyFactoryItem::~TEnemyFactoryItem()
{

}
