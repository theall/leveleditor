#ifndef TWALLLAYERITEM_H
#define TWALLLAYERITEM_H

#include "objectlayeritem.h"
#include "generic.hpp"
#include "objectitem/wallitem.h"

class TWallModel;
class TWallLayerItem : public TObjectLayerItem
{
    Q_OBJECT

public:
    explicit TWallLayerItem(TWallModel *wallsModel, QGraphicsItem *parent = Q_NULLPTR);
    ~TWallLayerItem();

private slots:
    DECL_GENERIC_SLOTS(Wall);

private:
    DECL_GENERIC_VARS(Wall);
};

#endif // TWALLLAYERITEM_H
