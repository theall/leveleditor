#include "tilelayeritem.h"
#include <QGraphicsScene>

TTileLayerItem::TTileLayerItem(TTileLayerModel *model, QGraphicsItem *parent) :
    TLayerItem(model, parent)
  , mLayer(model->layer())
{
    Q_ASSERT(mLayer);
    setLayerType(TLayerItem::TILE);
    connect(mLayer, SIGNAL(tileInserted(TTileList,QList<int>)), this, SLOT(slotTileInserted(TTileList,QList<int>)));
    connect(mLayer, SIGNAL(tileRemoved(TTileList,QList<int>)), this, SLOT(slotTileRemoved(TTileList,QList<int>)));

    create();
}

TTileLayerItem::~TTileLayerItem()
{

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
    QGraphicsScene *_scene = scene();
    if(!_scene)
        return;

    for(TTile *tile : tileList) {
        TTileItem *tileItem = mTileItemMap[tile];
        if(tileItem) {
            _scene->removeItem(tileItem);
        }
    }
    calcBoundingRect();
}

void TTileLayerItem::create()
{
    Q_ASSERT(mLayer);

    mTileItemMap.clear();
    for(TTile *tile : mLayer->tileList()) {
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
    mBoundingRect = QRectF();
    for(TTileItem *tileItem : mTileItemList) {
        mBoundingRect = mBoundingRect.united(tileItem->boundingRect());
    }
    return mBoundingRect;
}
