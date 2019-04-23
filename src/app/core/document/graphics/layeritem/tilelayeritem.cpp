#include "tilelayeritem.h"

TTileLayerItem::TTileLayerItem(TLayer *layer, QGraphicsItem *parent) :
    TLayerItem(parent)
  , mLayer(layer)
{
    Q_ASSERT(mLayer);

    QMap<TTile*, TTileItem*> tileItemMap;
    foreach (TTile *tile, mLayer->tileList()) {
        TTileItem *tileItem = new TTileItem(tile, this);
        mTileItemList.append(tileItem);
        tileItemMap.insert(tile, tileItem);
    }

    // Process follow target
    for(TTileItem *tileItem : mTileItemList) {
        TTile *target = tileItem->tile()->target();
        if(target) {
            tileItem->setTargetTileItem(tileItemMap[target]);
        }
    }

    calcBoundingRect();
}

QRectF TTileLayerItem::calcBoundingRect()
{
    mBoundingRect = QRectF();
    for(TTileItem *tileItem : mTileItemList) {
        mBoundingRect = mBoundingRect.united(tileItem->boundingRect());
    }
    return mBoundingRect;
}
