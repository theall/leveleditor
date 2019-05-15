#ifndef TWALLLAYERITEM_H
#define TWALLLAYERITEM_H

#include "objectlayeritem.h"

class TWallsModel;
class TWallLayerItem : public TObjectLayerItem
{
public:
    explicit TWallLayerItem(TWallsModel *wallsModel, QGraphicsItem *parent = Q_NULLPTR);
    ~TWallLayerItem();
};

#endif // TWALLLAYERITEM_H
