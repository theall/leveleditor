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
