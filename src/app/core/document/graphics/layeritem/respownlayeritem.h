#ifndef TRESPOWNLAYERITEM_H
#define TRESPOWNLAYERITEM_H

#include "layeritem.h"
#include "objectitem/respownpositem.h"
#include "objectitem/bornpositem.h"
#include "objectlayeritem.h"

class TRespawnModel;
class TRespownLayerItem : public TObjectLayerItem
{
public:
    TRespownLayerItem(TRespawnModel *respawnModel, QGraphicsItem *parent = Q_NULLPTR);
    ~TRespownLayerItem();

private:
    TBornPosItemList mBornPosItemList;
    TRespownPosItemList mRespownPosItemList;

};

#endif // TRESPOWNLAYERITEM_H
