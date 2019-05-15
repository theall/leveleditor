#ifndef TBOXLAYERITEM_H
#define TBOXLAYERITEM_H

#include "objectlayeritem.h"

class TBoxesModel;
class TBoxLayerItem : public TObjectLayerItem
{
public:
    explicit TBoxLayerItem(TBoxesModel *boxesModel, QGraphicsItem *parent = Q_NULLPTR);
    ~TBoxLayerItem();
};

#endif // TBOXLAYERITEM_H
