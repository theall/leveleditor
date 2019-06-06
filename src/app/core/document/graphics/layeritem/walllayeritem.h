#ifndef TWALLLAYERITEM_H
#define TWALLLAYERITEM_H

#include "objectlayeritem.h"

class TWallModel;
class TWallLayerItem : public TObjectLayerItem
{
public:
    explicit TWallLayerItem(TWallModel *wallsModel, QGraphicsItem *parent = Q_NULLPTR);
    ~TWallLayerItem();
};

#endif // TWALLLAYERITEM_H
