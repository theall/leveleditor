#include "sceneitem.h"

TSceneItem::TSceneItem(TSceneModel *sceneModel, QGraphicsItem *parent) :
    QGraphicsObject(parent)
  , mSceneModel(sceneModel)
  , mDarkRectangle(new QGraphicsRectItem(this))
  , mBorderRectangle(new QGraphicsRectItem(this))
{
    Q_ASSERT(mSceneModel);
    setFlag(QGraphicsItem::ItemHasNoContents);
    setAcceptHoverEvents(true);

    foreach (TLayer *layer, mSceneModel->layersModel()->layerList()) {
        TLayerItem *layerItem = new TLayerItem(layer, this);
        mLayerItemList.append(layerItem);
    }
}

TSceneItem::~TSceneItem()
{

}

void TSceneItem::calcBoundingRect()
{
    mBoundingRect.intersected(QRectF(0,0,0,0));
    foreach (TLayerItem *layerItem, mLayerItemList) {
        mBoundingRect = mBoundingRect.united(layerItem->calcBoundingRect());
    }
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
