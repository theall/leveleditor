#ifndef TDAREALAYERITEM_H
#define TDAREALAYERITEM_H

#include "objectlayeritem.h"
#include "generic.hpp"
#include "objectitem/dareaitem.h"

class TDAreaModel;
class TDAreaLayerItem : public TObjectLayerItem
{
    Q_OBJECT

public:
    explicit TDAreaLayerItem(TDAreaModel *dAreasModel, QGraphicsItem *parent = Q_NULLPTR);
    ~TDAreaLayerItem();

private slots:
    DECL_GENERIC_SLOTS(DArea);

private:
    DECL_GENERIC_VARS(DArea);
};

#endif // TDAREALAYERITEM_H
