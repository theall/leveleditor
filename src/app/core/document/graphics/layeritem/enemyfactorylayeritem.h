#ifndef TENEMYFACTORYLAYERITEM_H
#define TENEMYFACTORYLAYERITEM_H

#include "objectlayeritem.h"
#include "objectitem/enemyfactoryitem.h"

class TEnemyFactoryModel;
class TEnemyFactoryLayerItem : public TObjectLayerItem
{
    Q_OBJECT

public:
    explicit TEnemyFactoryLayerItem(TEnemyFactoryModel *enemyFactoryModel, QGraphicsItem *parent = Q_NULLPTR);
    ~TEnemyFactoryLayerItem();

private slots:
    void slotBoundingRectChanged(const QRectF &boundingRect);

private:
    TEnemyFactoryItemList mEnemyFactoryList;

    // TLayerItem interface
public:
    virtual QList<QGraphicsItem *> childItems() const;
};


#endif // TENEMYFACTORYLAYERITEM_H
