#ifndef TDAREALAYERITEM_H
#define TDAREALAYERITEM_H

#include "objectlayeritem.h"

class TDAreasModel;
class TDAreaLayerItem : public TObjectLayerItem
{
public:
    explicit TDAreaLayerItem(TDAreasModel *dAreasModel, QGraphicsItem *parent = Q_NULLPTR);
    ~TDAreaLayerItem();
};

#endif // TDAREALAYERITEM_H
