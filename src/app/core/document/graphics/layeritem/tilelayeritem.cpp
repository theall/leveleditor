#include "tilelayeritem.h"

TTileLayerItem::TTileLayerItem(TTileLayerModel *model, QGraphicsItem *parent) :
    TLayerItem(model, parent)
  , mLayer(model->layer())
{
    setLayerType(TLayerItem::TILE);

    create();
}

TTileLayerItem::~TTileLayerItem()
{

}

void TTileLayerItem::create()
{
    Q_ASSERT(mLayer);

    QMap<TTile*, TTileItem*> tileItemMap;
    for(TTile *tile : mLayer->tileList()) {
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
