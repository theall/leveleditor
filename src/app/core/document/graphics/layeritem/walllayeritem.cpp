#include "walllayeritem.h"
#include "objectitem/wallitem.h"
#include "../../model/wallsmodel.h"

TWallLayerItem::TWallLayerItem(TWallsModel *wallsModel, QGraphicsItem *parent) :
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
