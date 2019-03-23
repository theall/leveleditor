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
    QPointF tilePos = mTile->getValue(PID_OBJECT_POS).toPointF();
    qreal tileTop = tilePos.y();
    qreal tileLeft = tilePos.x();
    if(!endPos1.isNull()) {
        if(endPos1.y() < 1)
            endPos1.setY(tileTop);
        else if(endPos1.x() < 1)
            endPos1.setX(tileLeft);
    }

    if(!endPos2.isNull()) {
        QSize tileSize = mTile->getValue(PID_OBJECT_SIZE).toSize();
        if(endPos2.y() < 1)
            endPos2.setY(tileTop + tileSize.height());
        else if(endPos2.x() < 1)
            endPos2.setX(tileLeft + tileSize.width());
    }
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
    painter->fillRect(mBoundingRect.adjusted(1,1,-1,-1), Qt::black);
}

void TDoorItem::propertyValueChanged(PropertyID pid)
{
    if(pid==PID_TILE_END_1 || pid==PID_TILE_END_2) {
        updateBoundingRect();
    }
}

TTrackItem::TTrackItem(TTile *tile, QGraphicsItem *parent) :
    TObjectItem(tile, parent)
  , mTile(tile)
{
    Q_ASSERT(mTile);

    mVector = mTile->getValue(PID_TILE_SPEED).toPointF();
}

TTrackItem::~TTrackItem()
{

}

QRectF TTrackItem::boundingRect() const
{
    return mBoundingRect;
}

void TTrackItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

}

void TTrackItem::propertyValueChanged(PropertyID pid)
{

}

TTileItem::TTileItem(TTile *tile, QGraphicsItem *parent) :
    TObjectItem(tile, parent)
  , mTile(tile)
  , mDoorItem(nullptr)
{
    Q_ASSERT(mTile);

    mBoundingRect = mTile->rect();

    QPointF endPos1 = mTile->getValue(PID_TILE_END_1).toPointF();
    QPointF endPos2 = mTile->getValue(PID_TILE_END_2).toPointF();
    if(!endPos1.isNull() && !endPos2.isNull()) {
        mDoorItem = new TDoorItem(tile, this);
    }
}

TTileItem::~TTileItem()
{
    if(mDoorItem)
        delete mDoorItem;
}

QRectF TTileItem::boundingRect() const
{
    QRectF r = mTile->rect();;
    if(mDoorItem)
        r = r.united(mDoorItem->boundingRect());
    return r;
}

void TTileItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QRectF r = mTile->rect();
    painter->drawPixmap(r.topLeft(), mTile->pixmap());
    painter->drawRect(r);

    if(mDoorItem) {
        QLineF trackLine(r.center(), mDoorItem->boundingRect().center());
        QColor gray(Qt::gray);
        gray.setAlpha(128);
        QPen pen(gray, 2, Qt::DotLine);
        pen.setCosmetic(true);
        painter->setPen(pen);
        painter->drawLine(trackLine);
    }
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
