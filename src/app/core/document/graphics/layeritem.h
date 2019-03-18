#ifndef TLAYERITEM_H
#define TLAYERITEM_H

#include <QList>
#include <QGraphicsObject>

#include "tileitem.h"
#include "../model/entity/layer.h"

class TLayerItem : public QGraphicsObject
{
public:
    TLayerItem(TLayer *layer, QGraphicsItem *parent = Q_NULLPTR);

    QRectF calcBoundingRect();

private:
    TLayer *mLayer;
    QRectF mBoundingRect;
    TTileItemList mTileItemList;

    // QGraphicsItem interface
public:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
};

typedef QList<TLayerItem*> TLayerItemList;
#endif // TLAYERITEM_H
