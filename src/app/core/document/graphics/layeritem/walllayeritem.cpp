#include "walllayeritem.h"
#include "objectitem/wallitem.h"
#include "../../model/wallmodel.h"

TWallLayerItem::TWallLayerItem(TWallModel *wallsModel, QGraphicsItem *parent) :
    TObjectLayerItem(wallsModel, parent)
{
    Q_ASSERT(wallsModel);

    for(TWall *wall : wallsModel->wallList()) {
        TWallItem *wallItem = new TWallItem(wall, this);
        mObjectItemList.append(wallItem);
    }

    calcBoundingRect();
}

TWallLayerItem::~TWallLayerItem()
{

}
