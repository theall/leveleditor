#include "mainlayeritem.h"
#include "objectitem/areaitem.h"
#include "../../model/scenemodel.h"

TMainLayerItem::TMainLayerItem(TSceneModel *sceneModel, QGraphicsItem *parent) :
    TLayerItem(parent)
  , mSceneModel(sceneModel)
{
    Q_ASSERT(mSceneModel);

    for(TArea *area : mSceneModel->getAreasModel()->areaList()) {
        TAreaItem *areaItem = new TAreaItem(area, this);
        mObjectItemList.append(areaItem);
    }

    calcBoundingRect();
}

TMainLayerItem::~TMainLayerItem()
{

}


QRectF TMainLayerItem::calcBoundingRect()
{
    mBoundingRect = QRectF();
    foreach (TObjectItem *objectItem, mObjectItemList) {
        mBoundingRect = mBoundingRect.united(objectItem->boundingRect());
    }
    return mBoundingRect;
}
