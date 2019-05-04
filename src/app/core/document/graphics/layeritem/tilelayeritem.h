#ifndef TILELAYERITEM_H
#define TILELAYERITEM_H

#include <QList>
#include "layeritem.h"
#include "objectitem/tileitem.h"
#include "../../model/tilelayermodel.h"

class TTileLayerItem : public TLayerItem
{
public:
    explicit TTileLayerItem(TLayer *layer, QGraphicsItem *parent = Q_NULLPTR);
    TTileLayerItem(TTileLayerModel *model, QGraphicsItem *parent = Q_NULLPTR);
    ~TTileLayerItem();

private:
    TLayer *mLayer;
    QRectF mBoundingRect;
    TTileItemList mTileItemList;

    void create();

    // TLayerItem interface
public:
    QRectF calcBoundingRect() Q_DECL_OVERRIDE;
};

typedef QList<TTileLayerItem*> TTileLayerItemList;
#endif // TILELAYERITEM_H
