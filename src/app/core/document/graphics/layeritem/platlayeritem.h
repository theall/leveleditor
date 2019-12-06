#ifndef TPLATLAYERITEM_H
#define TPLATLAYERITEM_H

#include "objectlayeritem.h"
#include "generic.hpp"
#include "objectitem/platitem.h"

class TPlatModel;
class TPlatLayerItem : public TObjectLayerItem
{
    Q_OBJECT

public:
    explicit TPlatLayerItem(TPlatModel *platformsModel, QGraphicsItem *parent = Q_NULLPTR);
    ~TPlatLayerItem();

private slots:
    DECL_GENERIC_SLOTS(Plat);

private:
    DECL_GENERIC_VARS(Plat);
};

#endif // TPLATLAYERITEM_H
