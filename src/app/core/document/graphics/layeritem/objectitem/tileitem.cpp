#include "tileitem.h"

#include <QCursor>
#include <QGraphicsSceneMouseEvent>

TTileItem::TTileItem(TTile *tile, QGraphicsItem *parent) :
    TObjectItem(tile, parent)
  , mTile(tile)
  , mDoorItem(nullptr)
  , mTileDoorTrackItem(nullptr)
{
    Q_ASSERT(mTile);

    mBoundingRect = mTile->rect();

    if(mTile->hasMoveModel()) {
        mDoorItem = new TDoorItem(this);
        mTileDoorTrackItem = new TTrackItem(this, mDoorItem);
    }
}

TTileItem::~TTileItem()
{
    if(mDoorItem)
        delete mDoorItem;
    if(mTileDoorTrackItem)
        delete mTileDoorTrackItem;

}

TTile *TTileItem::tile() const
{
    return mTile;
}

TDoor *TTileItem::door() const
{
    return mTile->door();
}

TTileItem *TTileItem::targetTileItem() const
{
    return mTargetTileItem;
}

void TTileItem::setTargetTileItem(TTileItem *targetTileItem)
{
    mTargetTileItem = targetTileItem;
}

QRectF TTileItem::boundingRect() const
{
    return mTile->rect();
}

void TTileItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QRectF r = mTile->rect();
    painter->drawPixmap(r.topLeft(), mTile->pixmap());
    painter->drawRect(r);
}

QPainterPath TTileItem::shape() const
{
    QPainterPath painterPath;
    painterPath.addRect(mTile->rect());
    return painterPath;
}

void TTileItem::propertyValueChanged(PropertyID pid)
{
    if(pid==PID_OBJECT_POS) {
        // Position changed, synchrony update door's position
    }
}
