#ifndef TTILEITEM_H
#define TTILEITEM_H

#include <QList>
#include "tileitem/dooritem.h"
#include "tileitem/trackitem.h"
#include "../../../model/entity/tile.h"

class TTileItem : public TObjectItem
{
    Q_OBJECT

public:
    TTileItem(TTile *tile, QGraphicsItem *parent = Q_NULLPTR);
    ~TTileItem();

    TTile *tile() const;
    TDoor *door() const;

    TTileItem *targetTileItem() const;
    void setTargetTileItem(TTileItem *targetTileItem);

private:
    TTile *mTile;
    TDoorItem *mDoorItem;
    TTrackItem *mTileDoorTrackItem;
    TTileItem *mTargetTileItem;

    // QGraphicsItem interface
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;

    // TObjectItem interface
public:
    void propertyValueChanged(PropertyID pid) Q_DECL_OVERRIDE;
};

typedef QList<TTileItem*> TTileItemList;
#endif // TTILEITEM_H
