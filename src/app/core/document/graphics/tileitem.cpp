#include "tileitem.h"

TDoorItem::TDoorItem(TTile *tile, QGraphicsItem *parent) :
    TObjectItem(tile, parent)
  , mTile(tile)
{
    updateBoundingRect();
}

void TDoorItem::updateBoundingRect()
{
    QPointF endPos1 = mTile->getValue(PID_TILE_END_1).toPointF();
    QPointF endPos2 = mTile->getValue(PID_TILE_END_2).toPointF();
    mBoundingRect.setTopLeft(endPos1);
    mBoundingRect.setBottomRight(endPos2);
}

QRectF TDoorItem::boundingRect() const
{
    return mBoundingRect;
}

void TDoorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QColor gray(Qt::gray);
    gray.setAlpha(128);
    QPen pen(gray, 2, Qt::DotLine);
    pen.setCosmetic(true);
    painter->setPen(pen);
    painter->drawRect(mBoundingRect);
    painter->fillRect(mBoundingRect.adjusted(1,1,-1,-1), Qt::blue);
}

void TDoorItem::propertyValueChanged(PropertyID pid)
{
    if(pid==PID_TILE_END_1 || pid==PID_TILE_END_2) {
        updateBoundingRect();
    }
}

TTileItem::TTileItem(TTile *tile, QGraphicsItem *parent) :
    TObjectItem(tile, parent)
  , mTile(tile)
  , mDoorItem(new TDoorItem(tile, this))
{
    Q_ASSERT(mTile);

    mBoundingRect = mTile->rect();
}

TTileItem::~TTileItem()
{
    delete mDoorItem;
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
    if(pid==PID_OBJECT_POS || pid==PID_OBJECT_SIZE) {

    }
}
