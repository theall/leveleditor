#ifndef TBOXLAYERITEM_H
#define TBOXLAYERITEM_H

#include "objectlayeritem.h"
#include "generic.hpp"
#include "objectitem/boxitem.h"

class TBoxModel;
class TBoxLayerItem : public TObjectLayerItem
{
    Q_OBJECT

public:
    explicit TBoxLayerItem(TBoxModel *boxesModel, QGraphicsItem *parent = Q_NULLPTR);
    ~TBoxLayerItem();

private slots:
    DECL_GENERIC_SLOTS(Box);

private:
    DECL_GENERIC_VARS(Box);
};

#endif // TBOXLAYERITEM_H
