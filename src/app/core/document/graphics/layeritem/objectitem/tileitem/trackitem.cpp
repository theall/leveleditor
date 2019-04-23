#include "trackitem.h"
#include <QPen>
#include <QPainter>

TTrackItem::TTrackItem(TObjectItem *parent, TObjectItem *child) :
    QGraphicsItem(parent)
  , mHostObjectItem(parent)
  , mChildObjectItem(child)
{
    Q_ASSERT(mHostObjectItem);
    Q_ASSERT(mChildObjectItem);
}

TTrackItem::~TTrackItem()
{

}

TObjectItem *TTrackItem::childObjectItem() const
{
    return mChildObjectItem;
}

void TTrackItem::setChildObjectItem(TObjectItem *childObjectItem)
{
    mChildObjectItem = childObjectItem;
}

TObjectItem *TTrackItem::hostObjectItem() const
{
    return mHostObjectItem;
}

void TTrackItem::setHostObjectItem(TObjectItem *hostObjectItem)
{
    mHostObjectItem = hostObjectItem;
}

QRectF TTrackItem::boundingRect() const
{
    return mHostObjectItem->boundingRect().united(mChildObjectItem->boundingRect());
}

void TTrackItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPointF p1 = mHostObjectItem->boundingRect().center();
    QPointF p2 = mChildObjectItem->boundingRect().center();
    QLineF trackLine(p1, p2);
    QColor gray(Qt::gray);
    gray.setAlpha(128);
    QPen pen(gray, 1, Qt::DotLine);
    pen.setCosmetic(true);
    painter->setPen(pen);
    painter->drawLine(trackLine);
}
