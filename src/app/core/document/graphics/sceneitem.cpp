#include "sceneitem.h"
#include "layeritem/tilelayeritem.h"
#include "layeritem/arealayeritem.h"
#include "layeritem/boxlayeritem.h"
#include "layeritem/darealayeritem.h"
#include "layeritem/platlayeritem.h"
#include "layeritem/walllayeritem.h"
#include "layeritem/triggerlayeritem.h"
#include "layeritem/propertylayeritem.h"
#include "layeritem/enemyfactorylayeritem.h"
#include "layeritem/objectitem/animationitem.h"

#include "uiitem/darkmaskitem.h"

#include "../model/areamodel.h"
#include "../model/boxmodel.h"
#include "../model/dareamodel.h"
#include "../model/platmodel.h"
#include "../model/wallmodel.h"

#include <QDebug>

#define ZINDEX_TOP 1000

TSceneItem::TSceneItem(TSceneModel *sceneModel, QGraphicsItem *parent) :
    QGraphicsObject(parent)
  , mIsHovered(false)
  , mSceneModel(sceneModel)
  , mBorderRectangle(new QGraphicsRectItem(this))
  , mCurrentLayerItem(nullptr)
  , mDarkMaskItem(new TDarkMaskItem(this))
  , mPropertylayerItem(new TPropertyLayerItem(sceneModel, this))
{
    Q_ASSERT(sceneModel);

    setFlag(QGraphicsItem::ItemHasNoContents);
    setAcceptHoverEvents(true);

    connect(mSceneModel, SIGNAL(currentIndexChanged(int)), this, SLOT(slotOnSceneModelCurrentIndexChanged(int)));

    TAnimationItemList animationItemList;
    for(TBaseModel *baseModel : mSceneModel->getBaseModelList()) {
        TLayerItem *layerItem = nullptr;
        if(TTileLayerModel *tileLayerModel = dynamic_cast<TTileLayerModel*>(baseModel)) {
            layerItem = new TTileLayerItem(tileLayerModel, this);
            mTileLayerItemList.append((TTileLayerItem*)layerItem);
        } else if(TAreaModel *areaModel = dynamic_cast<TAreaModel*>(baseModel)) {
            layerItem = new TAreaLayerItem(areaModel, this);
        } else if(TBoxModel *boxModel = dynamic_cast<TBoxModel*>(baseModel)) {
            layerItem = new TBoxLayerItem(boxModel, this);
        } else if(TDAreaModel *dareasModel = dynamic_cast<TDAreaModel*>(baseModel)) {
            layerItem = new TDAreaLayerItem(dareasModel, this);
        } else if(TPlatModel *platModel = dynamic_cast<TPlatModel*>(baseModel)) {
            layerItem = new TPlatLayerItem(platModel, this);
        } else if(TWallModel *wallModel = dynamic_cast<TWallModel*>(baseModel)) {
            layerItem = new TWallLayerItem(wallModel, this);
        } else if(TAnimationModel *animationModel = dynamic_cast<TAnimationModel*>(baseModel)) {
            for(TFrameModel *frameModel : animationModel->frameModelList()) {
                TAnimation *animation = frameModel->animation();
                if(!animation || !animation->getTile())
                    continue;
                TAnimationItem *item = new TAnimationItem(frameModel->animation(), nullptr);
                animationItemList.append(item);
            }
        } else if(TEnemyFactoryModel *enemyFactoryModel = dynamic_cast<TEnemyFactoryModel*>(baseModel)) {
            layerItem = new TEnemyFactoryLayerItem(enemyFactoryModel, this);
        } else if(TTriggerModel *triggerModel = dynamic_cast<TTriggerModel*>(baseModel)) {
            layerItem = new TTriggerLayerItem(triggerModel, this);
        }
        if(layerItem) {
            connect(layerItem, SIGNAL(boundingRectChanged(QRectF)), this, SLOT(slotLayerBoundingRectChanged(QRectF)));
            mBoundingRect = mBoundingRect.united(layerItem->boundingRect());
        } else {
            qDebug() << "Unprocessed model:" << baseModel->name();
        }
        internalAdd(baseModel, layerItem);

        if(baseModel == mSceneModel->getCurrentModel())
            mCurrentLayerItem = layerItem;
    }

    internalAdd(sceneModel, mPropertylayerItem);

    // Replace animation item into tilelayeritem
    for(TAnimationItem *animationItem : animationItemList) {
        for(TTileLayerItem *tileLayerItem : mTileLayerItemList) {
           tileLayerItem->replace(animationItem);
        }
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
//            for(TLayerItem *layerItem : mLayerItemList) {
//                layerItem->setVisible(false);
//            }
//            layerItem->setVisible(true);
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
    mDarkMaskItem->setVisible(false);
    mDarkMaskItem->setVisible(index>0 && baseModel);
}

void TSceneItem::slotLayerBoundingRectChanged(const QRectF &rect)
{
    if(mBoundingRect.contains(rect))
        return;

    mBoundingRect = mBoundingRect.united(rect);
    emit boundingRectChanged(mBoundingRect);
}

void TSceneItem::slotSceneModelPropertyItemValueChanged(TPropertyItem *, const QVariant &)
{

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

void TSceneItem::internalAdd(TBaseModel *baseModel, TLayerItem *layerItem)
{
    if(!baseModel || !layerItem)
        return;

    mModelLayerMap[baseModel] = layerItem;
    mLayerItemList.append(layerItem);
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

void TSceneItem::step()
{
    for(TTileLayerItem *tileLayerItem : mTileLayerItemList) {
        if(!tileLayerItem)
            continue;

        tileLayerItem->step();
    }
}
