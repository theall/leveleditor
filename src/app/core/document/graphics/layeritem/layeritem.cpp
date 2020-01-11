#include "layeritem.h"
#include "objectitem/objectitem.h"
#include "../../model/basemodel.h"

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

bool TLayerItem::isFactoryLayer() const
{
    return mBaseModel->type()==TBaseModel::ENEMY_FACTORY;
}

QList<QGraphicsItem *> TLayerItem::childItems() const
{
    return QGraphicsObject::childItems();
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
    QList<QGraphicsItem*> childItemsList = childItems();
    if(childItemsList.isEmpty())
        return QRectF();

    QRectF newRect = childItemsList.takeFirst()->boundingRect();
    for(QGraphicsItem *item : childItemsList) {
        QRectF itemRect = item->boundingRect();
        if(!itemRect.isValid())
            continue;
        newRect = newRect.united(itemRect);
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

void TLayerItem::promote(qreal zIndex)
{
    mSavedZIndex = zValue();
    setZValue(zIndex);
}

void TLayerItem::restore()
{
    setZValue(mSavedZIndex);
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
