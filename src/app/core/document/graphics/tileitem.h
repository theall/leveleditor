#ifndef TTILEITEM_H
#define TTILEITEM_H

#include <QList>
#include "objectitem.h"
#include "../model/entity/tile.h"

class TTileItem : public TObjectItem
{
public:
    TTileItem(TTile *tile, QGraphicsItem *parent = Q_NULLPTR);

private:
    TTile *mTile;

    // QGraphicsItem interface
public:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
};

typedef QList<TTileItem*> TTileItemList;
#endif // TTILEITEM_H
