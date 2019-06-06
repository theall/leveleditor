#include "platlayeritem.h"
#include "objectitem/platitem.h"
#include "../../model/platmodel.h"

TPlatLayerItem::TPlatLayerItem(TPlatModel *platformsModel, QGraphicsItem *parent) :
    TObjectLayerItem(platformsModel, parent)
{
    Q_ASSERT(platformsModel);

    for(TPlat *plat : platformsModel->platList()) {
        TPlatItem *platItem = new TPlatItem(plat, this);
        mObjectItemList.append(platItem);
    }

    calcBoundingRect();
}

TPlatLayerItem::~TPlatLayerItem()
{

}
