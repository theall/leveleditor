#include "resizeitem.h"

#include <QPainter>

#define HANDLE_WIDTH 9
#define MARGIN (HANDLE_WIDTH/2)

THandleItem::THandleItem(const HandleAnchor &handleAnchor, QGraphicsItem *parent) :
    QGraphicsItem(parent)
  , mAnchor(handleAnchor)
  , mBoudingRect(QRectF(-MARGIN,-MARGIN,HANDLE_WIDTH,HANDLE_WIDTH))
{
    setAcceptHoverEvents(false);
}

HandleAnchor THandleItem::anchor() const
{
    return mAnchor;
}

void THandleItem::setPos(float x, float y)
{
    mPoint.setX(x);
    mPoint.setY(y);
}

void THandleItem::setPos(const QPointF &pos)
{
    mPoint = pos;
}

QRectF THandleItem::boundingRect() const
{
    QRectF r(-HANDLE_WIDTH/2, -HANDLE_WIDTH/2, HANDLE_WIDTH, HANDLE_WIDTH);
    r.translate(mPoint);
    return r;
}

void THandleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawRect(boundingRect());
}

TResizeItem::TResizeItem(QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
    for(int i=0;i<HA_COUNT;i++) {
        mHandleItems[i] = new THandleItem((HandleAnchor)i, this);
    }
    setVisible(false);
}

void TResizeItem::setRect(const QRectF &rect)
{
    float left = rect.left();
    float top = rect.top();
    float width = rect.width();
    float height = rect.height();
    float halfWidthX = left + width / 2;
    float halfHeightY = top + height / 2;
    float right = rect.right();
    float bottom = rect.bottom();
    for(int i=0;i<HA_COUNT;i++) {
        THandleItem *handItem = mHandleItems[i];
        HandleAnchor anchor = handItem->anchor();
        switch (anchor) {
        case HA_TOP_CENTER:
            handItem->setPos(halfWidthX, top);
            break;
        case HA_TOP_RIGHT:
            handItem->setPos(right, top);
            break;
        case HA_LEFT_CENTER:
            handItem->setPos(left, halfHeightY);
            break;
        case HA_RIGHT_CENTER:
            handItem->setPos(right, halfHeightY);
            break;
        case HA_LEFT_BOTTOM:
            handItem->setPos(left, bottom);
            break;
        case HA_BOTTOM_CENTER:
            handItem->setPos(halfWidthX, bottom);
            break;
        case HA_BOTTOM_RIGHT:
            handItem->setPos(right, bottom);
            break;
        case HA_LEFT_TOP:
        default:
            handItem->setPos(left, top);
            break;
        }
    }
    mBoundingRect = rect;
    mBoundingRect.adjust(-MARGIN, -MARGIN, MARGIN, MARGIN);
}

QRectF TResizeItem::boundingRect() const
{
    return mBoundingRect;
}

void TResizeItem::paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *)
{
    //p->drawRect(mBoundingRect);
}
