#ifndef TBOXLAYERITEM_H
#define TBOXLAYERITEM_H

#include "objectlayeritem.h"

class TBoxModel;
class TBoxLayerItem : public TObjectLayerItem
{
public:
    explicit TBoxLayerItem(TBoxModel *boxesModel, QGraphicsItem *parent = Q_NULLPTR);
    ~TBoxLayerItem();
};

#endif // TBOXLAYERITEM_H
