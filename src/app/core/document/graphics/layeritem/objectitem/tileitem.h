#ifndef TTILEITEM_H
#define TTILEITEM_H

#include <QList>

#include "pointobjectitem.h"
#include "tileitem/dooritem.h"
#include "tileitem/trackitem.h"
#include "../../../model/entity/tile.h"

class TTileItem : public TPointObjectItem
{
    Q_OBJECT

public:
    TTileItem(TTile *tile, QGraphicsItem *parent = Q_NULLPTR);
    ~TTileItem();

    TTile *tile() const;
    void setTile(TTile *tile);

    TDoor *door() const;

    TTileItem *targetTileItem() const;
    void setTargetTileItem(TTileItem *targetTileItem);

    static bool showBorder();
    static void setShowBorder(bool showBorder);

    virtual void step() Q_DECL_OVERRIDE;

private:
    TTile *mTile;
    TDoorItem *mDoorItem;
    TTrackItem *mTileDoorTrackItem;
    TTileItem *mTargetTileItem;
    static bool mShowBorder;

    // QGraphicsItem interface
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    // TObjectItem interface
public:
    void propertyValueChanged(PropertyID pid) Q_DECL_OVERRIDE;
};

typedef QList<TTileItem*> TTileItemList;
#endif // TTILEITEM_H
