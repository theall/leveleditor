#include "tileitem.h"

#include <QCursor>
#include <QGraphicsSceneMouseEvent>

bool TTileItem::mShowBorder = false;
TTileItem::TTileItem(TTile *tile, QGraphicsItem *parent) :
    TPointObjectItem(tile, parent)
  , mTile(tile)
  , mDoorItem(nullptr)
  , mTileDoorTrackItem(nullptr)
{
    Q_ASSERT(mTile);

    if(mTile->hasMoveModel()) {
        mDoorItem = new TDoorItem(this);
        mTileDoorTrackItem = new TTrackItem(this, mDoorItem);
    }

    setBoundingRect(mTile->getRect()); 
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

void TTileItem::setTile(TTile *tile)
{
    if(mTile == tile)
        return;

    mTile = tile;
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

bool TTileItem::showBorder()
{
    return mShowBorder;
}

void TTileItem::setShowBorder(bool showBorder)
{
    mShowBorder = showBorder;
}

void TTileItem::step()
{
    if(!mTile)
        return;

    QPointF speed = mTile->getSpeed();
    if(speed.x() > 0.01 || speed.y() > 0.01) {
        mCurrentPos += speed;
    }
}

void TTileItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(mCurrentPos, mTile->pixmap());

    if(mShowBorder)
        TObjectItem::paint(painter, option, widget);
}

void TTileItem::propertyValueChanged(PropertyID pid)
{
    if(pid==PID_OBJECT_POS) {
        // Position changed, synchrony update door's position
    }
}
