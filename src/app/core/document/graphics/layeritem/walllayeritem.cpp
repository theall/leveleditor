#include "walllayeritem.h"
#include "../../model/wallmodel.h"

TWallLayerItem::TWallLayerItem(TWallModel *wallsModel, QGraphicsItem *parent) :
    TObjectLayerItem(wallsModel, parent)
{
    Q_ASSERT(wallsModel);

    CONNECT_GENERIC_SLOTS(wallsModel,Wall);

    for(TWall *wall : wallsModel->wallList()) {
        internalAdd(wall);
    }

    calcBoundingRect();
}

TWallLayerItem::~TWallLayerItem()
{

}

IMPL_GENERIC_SLOTS(Wall)
