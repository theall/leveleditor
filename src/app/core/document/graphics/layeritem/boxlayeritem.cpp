#include "boxlayeritem.h"
#include "../../model/boxmodel.h"

TBoxLayerItem::TBoxLayerItem(TBoxModel *boxesModel, QGraphicsItem *parent) :
    TObjectLayerItem(boxesModel, parent)
{
    Q_ASSERT(boxesModel);

    CONNECT_GENERIC_SLOTS(boxesModel,Box );

    for(TBox *box : boxesModel->boxList()) {
        internalAdd(box);
    }

    calcBoundingRect();
}

TBoxLayerItem::~TBoxLayerItem()
{

}

IMPL_GENERIC_SLOTS(Box)
