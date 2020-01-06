#include "enemyfactorylayeritem.h"

#include "../../model/enemyfactorymodel.h"

TEnemyFactoryLayerItem::TEnemyFactoryLayerItem(TEnemyFactoryModel *enemyFactoryModel, QGraphicsItem *parent) :
    TObjectLayerItem(enemyFactoryModel, parent)
{
    Q_ASSERT(enemyFactoryModel);

    for(TEnemyModel *enemyModel : enemyFactoryModel->enemyModelList()) {
        TEnemyFactoryItem *enemyFactoryItem = new TEnemyFactoryItem(enemyModel, this);
        connect(enemyFactoryItem,
                SIGNAL(boundingRectChanged(QRectF)),
                this,
                SLOT(slotBoundingRectChanged(QRectF)));
        mEnemyFactoryList.append(enemyFactoryItem);
    }

    calcBoundingRect();
}

TEnemyFactoryLayerItem::~TEnemyFactoryLayerItem()
{

}

QList<QGraphicsItem *> TEnemyFactoryLayerItem::childItems() const
{
    QList<QGraphicsItem *> itemsList = TObjectLayerItem::childItems();
    QList<QGraphicsItem *> enemyItemsList = itemsList;
    for(QGraphicsItem *item : itemsList) {
        enemyItemsList.append(item->childItems());
    }
    return enemyItemsList;
}

void TEnemyFactoryLayerItem::slotBoundingRectChanged(const QRectF &)
{
    calcBoundingRect();
}
