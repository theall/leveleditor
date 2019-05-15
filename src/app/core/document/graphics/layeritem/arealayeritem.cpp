#include "arealayeritem.h"
#include "objectitem/areaitem.h"
#include "../../model/areasmodel.h"

TAreasLayerItem::TAreasLayerItem(TAreasModel *areasModel, QGraphicsItem *parent) :
    TObjectLayerItem(areasModel, parent)
{
    Q_ASSERT(areasModel);

    for(TArea *area : areasModel->areaList()) {
        TAreaItem *areaItem = new TAreaItem(area, this);
        mObjectItemList.append(areaItem);
    }

    calcBoundingRect();
}

TAreasLayerItem::~TAreasLayerItem()
{

}
