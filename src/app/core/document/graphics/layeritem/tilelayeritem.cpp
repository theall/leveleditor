#include "tilelayeritem.h"
#include <QGraphicsScene>

TTileLayerItem::TTileLayerItem(TTileLayerModel *model, QGraphicsItem *parent) :
    TLayerItem(model, parent)
  , mTileLayerModel(model)
{
    Q_ASSERT(mTileLayerModel);
    setLayerType(TLayerItem::TILE);
    connect(mTileLayerModel, SIGNAL(tileInserted(TTileList,QList<int>)), this, SLOT(slotTileInserted(TTileList,QList<int>)));
    connect(mTileLayerModel, SIGNAL(tileRemoved(TTileList,QList<int>)), this, SLOT(slotTileRemoved(TTileList,QList<int>)));

    create();
}

TTileLayerItem::~TTileLayerItem()
{

}

bool TTileLayerItem::replace(TAnimationItem *animationItem)
{
    if(!animationItem)
        return false;

    TTile *tile = animationItem->getFirstTile();
    if(!mTileItemMap.contains(tile)) {
        return false;
    }
    TTileItem *tileItem = mTileItemMap[tile];
    mTileItemMap[tile] = animationItem;
    int index = mTileItemList.indexOf(tileItem);
    if(index == -1)
        return false;

    delete tileItem;
    animationItem->setParentItem(this);
    mTileItemList.replace(index, animationItem);
    return true;
}

void TTileLayerItem::step()
{
    for(TTileItem *tileItem : mTileItemList) {
        if(TAnimationItem *animationItem = dynamic_cast<TAnimationItem*>(tileItem))
            animationItem->step();
    }
}

void TTileLayerItem::slotTileInserted(const TTileList &tileList, const QList<int> &)
{
    TTileItemList tileItemList;
    for(TTile *tile : tileList) {
        TTileItem *tileItem = addTile(tile);
        tileItemList.append(tileItem);
    }

    for(TTileItem *tileItem : tileItemList) {
        setTileItemTarget(tileItem);
    }
    calcBoundingRect();
}

void TTileLayerItem::slotTileRemoved(const TTileList &tileList, const QList<int> &)
{
    for(TTile *tile : tileList) {
        TTileItem *tileItem = mTileItemMap[tile];
        if(tileItem) {
            //scene()->removeItem(tileItem);Don't use,will cause exception
            tileItem->disconnect(this);
            delete tileItem;
            mTileItemList.removeAll(tileItem);
        }
        mTileItemMap.remove(tile);
    }
    calcBoundingRect();
}

void TTileLayerItem::slotOnTileItemBoundingRectChanged(const QRectF &newRect)
{
    if(mBoundingRect.contains(newRect))
        return;

    setBoundingRect(mBoundingRect.united(newRect));
}

void TTileLayerItem::create()
{
    Q_ASSERT(mTileLayerModel);

    mTileItemMap.clear();
    for(TTile *tile : mTileLayerModel->tileList()) {
        addTile(tile);
    }

    // Process follow target
    for(TTileItem *tileItem : mTileItemList) {
        setTileItemTarget(tileItem);
    }

    calcBoundingRect();
}

TTileItem *TTileLayerItem::addTile(TTile *tile)
{
    TTileItem *tileItem = new TTileItem(tile, this);
    connect(tileItem, SIGNAL(boundingRectChanged(QRectF)), this, SLOT(slotOnTileItemBoundingRectChanged(QRectF)));
    mTileItemList.append(tileItem);
    mTileItemMap.insert(tile, tileItem);
    return tileItem;
}

void TTileLayerItem::setTileItemTarget(TTileItem *tileItem)
{
    if(!tileItem)
        return;

    TTile *target = tileItem->tile()->target();
    if(target) {
        TTileItem *targetTileItem = mTileItemMap[target];
        if(targetTileItem)
            tileItem->setTargetTileItem(targetTileItem);
    }
}

QRectF TTileLayerItem::calcBoundingRect()
{
    QRectF newRect;
    for(TTileItem *tileItem : mTileItemList) {
        newRect = newRect.united(tileItem->boundingRect());
    }
    setBoundingRect(newRect);
    return newRect;
}
