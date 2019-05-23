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
  , mBorderRectangle(new QGraphicsRectItem(this))
  , mCurrentLayerItem(nullptr)
  , mDarkMaskItem(new TDarkMaskItem(this))
{
    Q_ASSERT(mSceneModel);
    setFlag(QGraphicsItem::ItemHasNoContents);
    setAcceptHoverEvents(true);

    connect(mSceneModel, SIGNAL(currentIndexChanged(int)), this, SLOT(slotOnSceneModelCurrentIndexChanged(int)));

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
            connect(layerItem, SIGNAL(boundingRectChanged(QRectF)), this, SLOT(slotLayerBoundingRectChanged(QRectF)));
            mBoundingRect = mBoundingRect.united(layerItem->boundingRect());
        } else {
            qDebug() << "Unprocessed model:" << baseModel->name();
        }
        mModelLayerMap[baseModel] = layerItem;
        mLayerItemList.append(layerItem);
    }

    int index = 0;
    for(TLayerItem *layerItem : mLayerItemList) {
        if(!layerItem)
            continue;

        layerItem->setZValue(index++);
    }
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

void TSceneItem::slotOnSceneModelCurrentIndexChanged(int index)
{
    TBaseModel *baseModel = mSceneModel->getBaseModel(index);
    if(!baseModel) {
        setCurrentLayerItem(nullptr);
        for(TLayerItem *layerItem : mLayerItemList) {
            if(layerItem) {
                layerItem->setOpacity(1.0);
            }
        }
    } else {
        TLayerItem *layerItem = mModelLayerMap[baseModel];
        setCurrentLayerItem(layerItem);

        if(layerItem) {
            layerItem->setOpacity(1.0);
            mDarkMaskItem->setZValue(layerItem->zValue() - 0.5);
        }
        for(int i=index+1;i<mLayerItemList.size();i++) {
            TLayerItem *layerItem = mLayerItemList.at(i);
            if(layerItem) {
                layerItem->setOpacity(0.4);
            }
        }
    }
    mDarkMaskItem->setVisible(index>0 && baseModel);
}

void TSceneItem::slotLayerBoundingRectChanged(const QRectF &rect)
{
    if(mBoundingRect.contains(rect))
        return;
    mBoundingRect = mBoundingRect.united(rect);
    emit boundingRectChanged(mBoundingRect);
}

TLayerItem *TSceneItem::getCurrentLayerItem() const
{
    return mCurrentLayerItem;
}

void TSceneItem::setCurrentLayerItem(TLayerItem *currentLayerItem)
{
    mCurrentLayerItem = currentLayerItem;
}

void TSceneItem::calcBoundingRect()
{
    QRectF tempRect;
    for(TLayerItem *layerItem : mLayerItemList) {
        if(!layerItem)
            continue;
        tempRect = tempRect.united(layerItem->calcBoundingRect());
    }
    mBoundingRect = tempRect;
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
