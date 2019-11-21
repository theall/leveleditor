#include "tileitem.h"

#include <QCursor>
#include <QGraphicsSceneMouseEvent>

bool TTileItem::mShowBorder = false;
TTileItem::TTileItem(TTile *tile, QGraphicsItem *parent) :
    TObjectItem(tile, parent)
  , mTile(tile)
  , mDoorItem(nullptr)
  , mTileDoorTrackItem(nullptr)
{
    Q_ASSERT(mTile);
    mCurrentPos = mTile->pos();
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
    QPointF p = mCurrentPos;
    painter->drawPixmap(p, mTile->pixmap());

    if(mShowBorder)
        TObjectItem::paint(painter, option, widget);
}

QPainterPath TTileItem::shape() const
{
    QPainterPath painterPath;
    painterPath.addRect(mTile->rect());
    return painterPath;
}

void TTileItem::propertyValueChanged(PropertyID pid)
{
    if(pid==PID_OBJECT_RECT) {
        // Position changed, synchrony update door's position
    }
}
