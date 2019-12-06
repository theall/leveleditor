#ifndef TAREALAYERITEM_H
#define TAREALAYERITEM_H

#include "objectlayeritem.h"
#include "generic.hpp"
#include "objectitem/areaitem.h"

class TAreaModel;
class TAreaLayerItem : public TObjectLayerItem
{
    Q_OBJECT

public:
    explicit TAreaLayerItem(TAreaModel *areasModel, QGraphicsItem *parent = Q_NULLPTR);
    ~TAreaLayerItem();

private slots:
    DECL_GENERIC_SLOTS(Area);

private:
    TAreaModel *mAreasModel;

    DECL_GENERIC_VARS(Area);
};

#endif // TAREALAYERITEM_H
