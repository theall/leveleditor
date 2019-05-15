#include "objectlayeritem.h"

TObjectLayerItem::TObjectLayerItem(TBaseModel *baseModel, QGraphicsItem *parent) :
    TLayerItem(baseModel, parent)
{

}

TObjectLayerItem::~TObjectLayerItem()
{

}

QRectF TObjectLayerItem::calcBoundingRect()
{
    mBoundingRect = QRectF();
    for(TObjectItem *objectItem : mObjectItemList) {
        mBoundingRect = mBoundingRect.united(objectItem->boundingRect());
    }
    return mBoundingRect;
}
