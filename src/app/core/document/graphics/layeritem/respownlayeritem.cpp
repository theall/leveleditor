#include "respownlayeritem.h"
#include "objectitem/respownpositem.h"
#include "objectitem/bornpositem.h"
#include "../../model/respawnmodel.h"

TRespownLayerItem::TRespownLayerItem(TRespawnModel *respawnModel, QGraphicsItem *parent):
    TObjectLayerItem(respawnModel, parent)
{
    Q_ASSERT(respawnModel);

    for(TRespawn *respawn : respawnModel->respawnList()) {
        TBornPosItem *bornPosItem = new TBornPosItem(respawn, this);
        TRespownPosItem *respownPosItem = new TRespownPosItem(respawn, this);
        mBornPosItemList.append(bornPosItem);
        mRespownPosItemList.append(respownPosItem);
    }
}

TRespownLayerItem::~TRespownLayerItem()
{

}
