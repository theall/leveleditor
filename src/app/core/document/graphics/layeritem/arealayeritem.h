#ifndef TAREALAYERITEM_H
#define TAREALAYERITEM_H

#include "objectlayeritem.h"

class TAreasModel;
class TAreasLayerItem : public TObjectLayerItem
{
public:
    explicit TAreasLayerItem(TAreasModel *areasModel, QGraphicsItem *parent = Q_NULLPTR);
    ~TAreasLayerItem();
};

#endif // TAREALAYERITEM_H
