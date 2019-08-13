#ifndef TENEMYFACTORYITEM_H
#define TENEMYFACTORYITEM_H

#include "objectlayeritem.h"

class TEnemyFactoryModel;
class TEnemyFactoryItem : public TObjectLayerItem
{
public:
    explicit TEnemyFactoryItem(TEnemyFactoryModel *enemyFactoryModel, QGraphicsItem *parent = Q_NULLPTR);
    ~TEnemyFactoryItem();
};

#endif // TENEMYFACTORYITEM_H
