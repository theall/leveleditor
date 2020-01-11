#include "enemyfactoryitem.h"
#include "../../../model/enemymodel.h"
#include "../../../model/entity/enemyfactory.h"

#include <QPainter>

TEnemyFactoryItem::TEnemyFactoryItem(TEnemyModel *enemyModel, QGraphicsItem *parent) :
    TObjectItem(enemyModel->enemyFactory(), parent)
{
    Q_ASSERT(enemyModel);

    for(TEnemy *enemy : enemyModel->objectList()) {
        addEnemy(enemy);
    }

    connect(enemyModel,
            SIGNAL(objectInserted(TEnemyList,QList<int>)),
            this,
            SLOT(slotEnemyInserted(TEnemyList,QList<int>)));
    connect(enemyModel,
            SIGNAL(objectRemoved(TEnemyList,QList<int>)),
            this,
            SLOT(slotEnemyRemoved(TEnemyList,QList<int>)));
}

TEnemyFactoryItem::~TEnemyFactoryItem()
{

}

void TEnemyFactoryItem::propertyValueChanged(PropertyID)
{

}

void TEnemyFactoryItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawRect(mBoundingRect);
}

void TEnemyFactoryItem::slotEnemyInserted(const TEnemyList &enemyList, const QList<int> &)
{
    for(TEnemy *enemy : enemyList) {
        addEnemy(enemy);
    }
    calcBoundingRect();
}

void TEnemyFactoryItem::slotEnemyRemoved(const TEnemyList &enemyList, const QList<int> &)
{
    calcBoundingRect();
}

void TEnemyFactoryItem::addEnemy(TEnemy *enemy)
{
    TEnemyItem *enemyItem = new TEnemyItem(enemy, this);
    connect(enemyItem,
            SIGNAL(boundingRectChanged(QRectF)),
            this,
            SLOT(slotBoundingRectChanged(QRectF)));
    mEnemyItemList.append(enemyItem);
}

void TEnemyFactoryItem::calcBoundingRect()
{
    QRectF newRect(0, 0, 1, 1);
    if(!mEnemyItemList.isEmpty())
        newRect = mEnemyItemList.first()->getBoundingRect();
    for(TEnemyItem *enemyItem : mEnemyItemList) {
        newRect = newRect.united(enemyItem->boundingRect());
    }
    setBoundingRect(newRect);
}

void TEnemyFactoryItem::slotBoundingRectChanged(const QRectF &boundingRect)
{
    calcBoundingRect();
}
