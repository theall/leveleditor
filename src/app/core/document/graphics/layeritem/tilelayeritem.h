#ifndef TILELAYERITEM_H
#define TILELAYERITEM_H

#include <QList>
#include "layeritem.h"
#include "objectitem/tileitem.h"
#include "../../model/entity/layer.h"

class TTileLayerItem : public TLayerItem
{
public:
    TTileLayerItem(TLayer *layer, QGraphicsItem *parent = Q_NULLPTR);

private:
    TLayer *mLayer;
    QRectF mBoundingRect;
    TTileItemList mTileItemList;

    // TLayerItem interface
public:
    QRectF calcBoundingRect() Q_DECL_OVERRIDE;
};

typedef QList<TTileLayerItem*> TTileLayerItemList;
#endif // TILELAYERITEM_H
