#ifndef TPLATLAYERITEM_H
#define TPLATLAYERITEM_H

#include "objectlayeritem.h"

class TPlatformsModel;
class TPlatLayerItem : public TObjectLayerItem
{
public:
    explicit TPlatLayerItem(TPlatformsModel *platformsModel, QGraphicsItem *parent = Q_NULLPTR);
    ~TPlatLayerItem();
};

#endif // TPLATLAYERITEM_H
