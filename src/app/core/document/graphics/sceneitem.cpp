#include "sceneitem.h"

#define ZINDEX_BASE 1000

TSceneItem::TSceneItem(TSceneModel *sceneModel, QGraphicsItem *parent) :
    QGraphicsObject(parent)
  , mSceneModel(sceneModel)
  , mDarkRectangle(new QGraphicsRectItem(this))
  , mBorderRectangle(new QGraphicsRectItem(this))
{
    Q_ASSERT(mSceneModel);
    setFlag(QGraphicsItem::ItemHasNoContents);
    setAcceptHoverEvents(true);

    for(TLayer *layer : mSceneModel->layersModel()->getBackgroundLayerList()) {
        TTileLayerItem *layerItem = new TTileLayerItem(layer, this);
        mLayerItemList.append(layerItem);
    }

    mLayerItemList.append(new TMainLayerItem(mSceneModel, this));

    for(TLayer *layer : mSceneModel->layersModel()->getForegroundLayerList()) {
        TTileLayerItem *layerItem = new TTileLayerItem(layer, this);
        mLayerItemList.append(layerItem);
    }

    int index = 0;
    for(TLayerItem *layerItem : mLayerItemList) {
        layerItem->setZValue(index++);
    }

    calcBoundingRect();
}

TSceneItem::~TSceneItem()
{

}

void TSceneItem::calcBoundingRect()
{
    mBoundingRect.intersected(QRectF(0,0,0,0));
    for(TLayerItem *layerItem : mLayerItemList) {
        mBoundingRect = mBoundingRect.united(layerItem->calcBoundingRect());
    }
    mBoundingRect.adjust(-100, -100, 100, 100);
}

QRectF TSceneItem::boundingRect() const
{
    return mBoundingRect;
}

void TSceneItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPen pen(Qt::green, 1, Qt::SolidLine);
    painter->setPen(pen);
    painter->drawRect(mBoundingRect);
}
