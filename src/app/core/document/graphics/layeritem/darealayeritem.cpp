#include "darealayeritem.h"
#include "objectitem/dareaitem.h"
#include "../../model/dareasmodel.h"

TDAreaLayerItem::TDAreaLayerItem(TDAreasModel *dAreasModel, QGraphicsItem *parent) :
    TObjectLayerItem(dAreasModel, parent)
{
    Q_ASSERT(dAreasModel);

    for(TDArea *darea : dAreasModel->dAreaList()) {
        TDAreaItem *dareaItem = new TDAreaItem(darea, this);
        mObjectItemList.append(dareaItem);
    }

    calcBoundingRect();
}

TDAreaLayerItem::~TDAreaLayerItem()
{

}
