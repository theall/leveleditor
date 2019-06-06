#include "darealayeritem.h"
#include "objectitem/dareaitem.h"
#include "../../model/dareamodel.h"

TDAreaLayerItem::TDAreaLayerItem(TDAreaModel *dAreasModel, QGraphicsItem *parent) :
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
