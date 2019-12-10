#include "objectlayeritem.h"

#define SCENE_SIZE 1920

TObjectLayerItem::TObjectLayerItem(TBaseModel *baseModel, QGraphicsItem *parent) :
    TLayerItem(baseModel, parent)
{
    setLayerType(TLayerItem::OBJECT);
}

TObjectLayerItem::~TObjectLayerItem()
{

}

QRectF TObjectLayerItem::calcBoundingRect()
{
    mBoundingRect = QRectF(0, 0, SCENE_SIZE, SCENE_SIZE);
    for(TObjectItem *objectItem : mObjectItemList) {
        mBoundingRect = mBoundingRect.united(objectItem->boundingRect());
    }
    return mBoundingRect;
}
