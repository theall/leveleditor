#include "sceneitem.h"
#include "layeritem/tilelayeritem.h"
#include "layeritem/arealayeritem.h"
#include "layeritem/boxlayeritem.h"
#include "layeritem/darealayeritem.h"
#include "layeritem/platlayeritem.h"
#include "layeritem/walllayeritem.h"
#include "../model/areasmodel.h"
#include "../model/boxesmodel.h"
#include "../model/dareasmodel.h"
#include "../model/platformsmodel.h"
#include "../model/wallsmodel.h"

#include <QDebug>

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

    for(TBaseModel *baseModel : mSceneModel->getBaseModelList()) {
        TLayerItem *layerItem = nullptr;
        if(TTileLayerModel *tileLayerModel = dynamic_cast<TTileLayerModel*>(baseModel)) {
            layerItem = new TTileLayerItem(tileLayerModel, this);
        } else if(TAreasModel *areaModel = dynamic_cast<TAreasModel*>(baseModel)) {
            layerItem = new TAreasLayerItem(areaModel, this);
        } else if(TBoxesModel *boxModel = dynamic_cast<TBoxesModel*>(baseModel)) {
            layerItem = new TBoxLayerItem(boxModel, this);
        } else if(TDAreasModel *dareasModel = dynamic_cast<TDAreasModel*>(baseModel)) {
            layerItem = new TDAreaLayerItem(dareasModel, this);
        } else if(TPlatformsModel *platModel = dynamic_cast<TPlatformsModel*>(baseModel)) {
            layerItem = new TPlatLayerItem(platModel, this);
        } else if(TWallsModel *wallModel = dynamic_cast<TWallsModel*>(baseModel)) {
            layerItem = new TWallLayerItem(wallModel, this);
        }
        if(layerItem) {
            mLayerItemList.append(layerItem);
        } else {
            qDebug() << "Unprocessed model:" << baseModel->name();
        }
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

TLayerItem *TSceneItem::getLayerItem(int index) const
{
    TLayerItem *layerItem = nullptr;
    if(index>=0 && index<mLayerItemList.size())
        layerItem = mLayerItemList.at(index);
    return layerItem;
}

TLayerItemList TSceneItem::getLayerItemList() const
{
    return mLayerItemList;
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
