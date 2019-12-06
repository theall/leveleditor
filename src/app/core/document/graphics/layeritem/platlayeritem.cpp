#include "platlayeritem.h"
#include "../../model/platmodel.h"

TPlatLayerItem::TPlatLayerItem(TPlatModel *platformsModel, QGraphicsItem *parent) :
    TObjectLayerItem(platformsModel, parent)
{
    Q_ASSERT(platformsModel);

    CONNECT_GENERIC_SLOTS(platformsModel,Plat);

    for(TPlat *plat : platformsModel->platList()) {
        internalAdd(plat);
    }

    calcBoundingRect();
}

TPlatLayerItem::~TPlatLayerItem()
{

}

IMPL_GENERIC_SLOTS(Plat)
