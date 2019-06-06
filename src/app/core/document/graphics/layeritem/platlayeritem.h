#ifndef TPLATLAYERITEM_H
#define TPLATLAYERITEM_H

#include "objectlayeritem.h"

class TPlatModel;
class TPlatLayerItem : public TObjectLayerItem
{
public:
    explicit TPlatLayerItem(TPlatModel *platformsModel, QGraphicsItem *parent = Q_NULLPTR);
    ~TPlatLayerItem();
};

#endif // TPLATLAYERITEM_H
