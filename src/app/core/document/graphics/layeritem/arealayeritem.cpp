#include "arealayeritem.h"
#include "../../model/areamodel.h"

TAreaLayerItem::TAreaLayerItem(TAreaModel *areasModel, QGraphicsItem *parent) :
    TObjectLayerItem(areasModel, parent)
{
    Q_ASSERT(areasModel);

    CONNECT_GENERIC_SLOTS(areasModel,Area);

    for(TArea *area : areasModel->areaList()) {
        internalAdd(area);
    }

    calcBoundingRect();
}

TAreaLayerItem::~TAreaLayerItem()
{

}

IMPL_GENERIC_SLOTS(Area)
