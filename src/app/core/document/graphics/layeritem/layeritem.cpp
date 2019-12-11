#include "layeritem.h"
#include "objectitem/objectitem.h"
#include "../../model/basemodel.h"

#define SCENE_WIDTH 1920
#define SCENE_HEIGHT 1080

TLayerItem::TLayerItem(TBaseModel *baseModel, QGraphicsItem *parent) :
    QGraphicsObject(parent)
  , mBaseModel(baseModel)
{
    connect(baseModel, SIGNAL(visibilityChanged(bool)), this, SLOT(slotLayerVisibilityChanged(bool)));
    connect(baseModel, SIGNAL(lockChanged(bool)), this, SLOT(slotLayerLockChanged(bool)));
}

TLayerItem::~TLayerItem()
{

}

TBaseModel *TLayerItem::baseModel() const
{
    return mBaseModel;
}

bool TLayerItem::locked() const
{
    return mLocked;
}

bool TLayerItem::isTileLayer() const
{
    return mLayerType==TILE;
}

bool TLayerItem::isObjectLayer() const
{
    return mLayerType==OBJECT;
}

TLayerItem::LayerType TLayerItem::layerType() const
{
    return mLayerType;
}

void TLayerItem::setLayerType(const LayerType &layerType)
{
    mLayerType = layerType;
}

bool TLayerItem::hasItem(TObjectItem *objectItem) const
{
    return objectItem && objectItem->parentItem()==this;
}

bool TLayerItem::hasItem(QGraphicsItem *objectItem) const
{
    return objectItem && objectItem->parentItem()==this;
}

TObjectItemList TLayerItem::getObjectItemList() const
{
    TObjectItemList objectItemList;
    for(QGraphicsItem *graphicsItem : childItems()) {
        if(TObjectItem *objectItem = dynamic_cast<TObjectItem*>(graphicsItem))
            objectItemList.append(objectItem);
    }
    return objectItemList;
}

QRectF TLayerItem::calcBoundingRect()
{
    QRectF newRect(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
    for(QGraphicsItem *item : childItems()) {
        newRect = newRect.united(item->boundingRect());
    }
    setBoundingRect(newRect);
    return newRect;
}

void TLayerItem::setBoundingRect(const QRectF &rect)
{
    if(mBoundingRect == rect)
        return;

    mBoundingRect = rect;
    emit boundingRectChanged(mBoundingRect);
}

void TLayerItem::step()
{

}

void TLayerItem::slotLayerVisibilityChanged(bool visible)
{
    setVisible(visible);
}

void TLayerItem::slotLayerLockChanged(bool locked)
{
    if(mLocked == locked)
        return;

    mLocked = locked;
}

QRectF TLayerItem::boundingRect() const
{
    return mBoundingRect;
}

void TLayerItem::paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *)
{

}
