#include "layeritem.h"
#include "objectitem/objectitem.h"
#include "../../model/basemodel.h"

TLayerItem::TLayerItem(TBaseModel *baseModel, QGraphicsItem *parent) :
    QGraphicsObject(parent)
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

void TLayerItem::slotLayerVisibilityChanged(bool visible)
{
    setVisible(visible);
}

void TLayerItem::slotLayerLockChanged(bool locked)
{
    mLocked = locked;
}

QRectF TLayerItem::boundingRect() const
{
    return mBoundingRect;
}

void TLayerItem::paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *)
{

}
