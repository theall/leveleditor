#include "boxlayeritem.h"
#include "objectitem/boxitem.h"
#include "../../model/boxesmodel.h"

TBoxLayerItem::TBoxLayerItem(TBoxesModel *boxesModel, QGraphicsItem *parent) :
    TObjectLayerItem(boxesModel, parent)
{
    Q_ASSERT(boxesModel);

    for(TBox *box : boxesModel->boxList()) {
        TBoxItem *boxItem = new TBoxItem(box, this);
        mObjectItemList.append(boxItem);
    }

    calcBoundingRect();
}

TBoxLayerItem::~TBoxLayerItem()
{

}
