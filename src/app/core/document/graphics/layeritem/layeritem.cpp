#include "layeritem.h"
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
