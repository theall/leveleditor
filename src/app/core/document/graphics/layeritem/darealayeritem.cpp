#include "darealayeritem.h"
#include "../../model/dareamodel.h"

TDAreaLayerItem::TDAreaLayerItem(TDAreaModel *dAreasModel, QGraphicsItem *parent) :
    TObjectLayerItem(dAreasModel, parent)
{
    Q_ASSERT(dAreasModel);

    CONNECT_GENERIC_SLOTS(dAreasModel,DArea);

    for(TDArea *dArea : dAreasModel->dAreaList()) {
        internalAdd(dArea);
    }

    calcBoundingRect();
}

TDAreaLayerItem::~TDAreaLayerItem()
{

}

IMPL_GENERIC_SLOTS(DArea)
