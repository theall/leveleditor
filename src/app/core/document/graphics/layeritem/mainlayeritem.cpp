#include "mainlayeritem.h"
#include "objectitem/areaitem.h"
#include "objectitem/boxitem.h"
#include "objectitem/platitem.h"
#include "objectitem/dareaitem.h"
#include "objectitem/wallitem.h"
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

    for(TBox *box : mSceneModel->getBoxesModel()->boxList()) {
        TBoxItem *boxItem = new TBoxItem(box, this);
        mObjectItemList.append(boxItem);
    }

    for(TPlat *plat : mSceneModel->getPlatformsModel()->platList()) {
        TPlatItem *platItem = new TPlatItem(plat, this);
        mObjectItemList.append(platItem);
    }

    for(TDArea *darea : mSceneModel->getDAreasModel()->dAreaList()) {
        TDAreaItem *dareaItem = new TDAreaItem(darea, this);
        mObjectItemList.append(dareaItem);
    }

    for(TWall *wall : mSceneModel->getWallsModel()->wallList()) {
        TWallItem *wallItem = new TWallItem(wall, this);
        mObjectItemList.append(wallItem);
    }

    calcBoundingRect();
}

TMainLayerItem::~TMainLayerItem()
{

}

QRectF TMainLayerItem::calcBoundingRect()
{
    mBoundingRect = QRectF();
    for(TObjectItem *objectItem : mObjectItemList) {
        mBoundingRect = mBoundingRect.united(objectItem->boundingRect());
    }
    return mBoundingRect;
}
