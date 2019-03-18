#include "tileitem.h"

TTileItem::TTileItem(TTile *tile, QGraphicsItem *parent) :
    TObjectItem(tile, parent)
  , mTile(tile)
{
    Q_ASSERT(mTile);

}

QRectF TTileItem::boundingRect() const
{
    return mTile->rect();
}

void TTileItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(mTile->rect().topLeft(), mTile->pixmap());
}
