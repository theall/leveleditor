#include "layeritem.h"

TLayerItem::TLayerItem(TLayer *layer, QGraphicsItem *parent) :
    QGraphicsObject(parent)
  , mLayer(layer)
{
    Q_ASSERT(mLayer);

    foreach (TTile *tile, mLayer->tileList()) {
        TTileItem *tileItem = new TTileItem(tile, this);
        mTileItemList.append(tileItem);
    }

    // Process follow target
    for(TTileItem *tileItem : mTileItemList) {

    }
}

QRectF TLayerItem::calcBoundingRect()
{
    mBoundingRect.setLeft(0);
    mBoundingRect.setRight(0);
    mBoundingRect.setTop(0);
    mBoundingRect.setBottom(0);
    foreach (TTileItem *tileItem, mTileItemList) {
        mBoundingRect = mBoundingRect.united(tileItem->boundingRect());
    }
    return mBoundingRect;
}

QRectF TLayerItem::boundingRect() const
{
    return mBoundingRect;
}

void TLayerItem::paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *)
{

}
