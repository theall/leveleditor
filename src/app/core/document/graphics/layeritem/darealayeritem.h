#ifndef TDAREALAYERITEM_H
#define TDAREALAYERITEM_H

#include "objectlayeritem.h"

class TDAreaModel;
class TDAreaLayerItem : public TObjectLayerItem
{
public:
    explicit TDAreaLayerItem(TDAreaModel *dAreasModel, QGraphicsItem *parent = Q_NULLPTR);
    ~TDAreaLayerItem();
};

#endif // TDAREALAYERITEM_H
