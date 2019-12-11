#ifndef TOBJECTLAYERITEM_H
#define TOBJECTLAYERITEM_H

#include "layeritem.h"
#include "objectitem/objectitem.h"

class TBaseModel;
class TObjectLayerItem : public TLayerItem
{
public:
    explicit TObjectLayerItem(TBaseModel *baseModel, QGraphicsItem *parent = Q_NULLPTR);
    ~TObjectLayerItem();

protected:
    TObjectItemList mObjectItemList;
};

#endif // TOBJECTLAYERITEM_H
