#ifndef TENEMYFACTORYLAYERITEM_H
#define TENEMYFACTORYLAYERITEM_H

#include "objectlayeritem.h"
#include "objectitem/enemyfactoryitem.h"

class TEnemyFactoryModel;
class TEnemyFactoryLayerItem : public TObjectLayerItem
{
public:
    explicit TEnemyFactoryLayerItem(TEnemyFactoryModel *enemyFactoryModel, QGraphicsItem *parent = Q_NULLPTR);
    ~TEnemyFactoryLayerItem();

private:
    TEnemyFactoryItemList mEnemyFactoryList;
};


#endif // TENEMYFACTORYLAYERITEM_H
