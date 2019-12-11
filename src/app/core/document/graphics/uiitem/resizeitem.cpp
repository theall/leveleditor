#include "resizeitem.h"

#include <QPainter>
#include <QCursor>

#define HANDLE_WIDTH 9
#define MARGIN (HANDLE_WIDTH/2)
#define HANDLE_FLATE_WIDTH (HANDLE_WIDTH*2)

THandleItem::THandleItem(const HandleAnchor &handleAnchor, QGraphicsItem *parent) :
    QGraphicsObject(parent)
  , mPoint(QPointF(0,0))
  , mAnchor(handleAnchor)
  , mPaintingRect(QRectF(-MARGIN,-MARGIN,HANDLE_WIDTH,HANDLE_WIDTH))
  , mBoundingRect(QRectF(-HANDLE_WIDTH,-HANDLE_WIDTH,HANDLE_FLATE_WIDTH,HANDLE_FLATE_WIDTH))
{
    setAcceptHoverEvents(false);
}

HandleAnchor THandleItem::anchor() const
{
    return mAnchor;
}

void THandleItem::setPos(float x, float y, bool emitSignal)
{
    setPos(QPointF(x, y), emitSignal);
}

void THandleItem::setPos(const QPointF &newPos, bool emitSignal)
{
    move(newPos-mPoint, emitSignal);
}

void THandleItem::move(const QPointF &offset, bool emitSignal)
{
    if(offset.isNull())
        return;

    if(emitSignal)
        emit moved(offset);
    else
        mPoint += offset;
}

QRectF THandleItem::boundingRect() const
{
    return mBoundingRect.translated(mPoint);
}

void THandleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(Qt::cyan);
    painter->drawRect(mPaintingRect.translated(mPoint));
}

TResizeItem::TResizeItem(QGraphicsItem *parent) :
    QGraphicsObject(parent)
{
    for(int i=0;i<HA_COUNT;i++) {
        mHandleItems[i] = new THandleItem((HandleAnchor)i, this);
        connect(mHandleItems[i], SIGNAL(moved(QPointF)), this, SLOT(slotHandleMoved(QPointF)));
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
            handItem->setPos(halfWidthX, top, false);
            break;
        case HA_TOP_RIGHT:
            handItem->setPos(right, top, false);
            break;
        case HA_LEFT_CENTER:
            handItem->setPos(left, halfHeightY, false);
            break;
        case HA_RIGHT_CENTER:
            handItem->setPos(right, halfHeightY, false);
            break;
        case HA_LEFT_BOTTOM:
            handItem->setPos(left, bottom, false);
            break;
        case HA_BOTTOM_CENTER:
            handItem->setPos(halfWidthX, bottom, false);
            break;
        case HA_BOTTOM_RIGHT:
            handItem->setPos(right, bottom, false);
            break;
        case HA_LEFT_TOP:
        default:
            handItem->setPos(left, top, false);
            break;
        }
    }
    mBoundingRect = rect.adjusted(-HANDLE_WIDTH, -HANDLE_WIDTH, HANDLE_WIDTH, HANDLE_WIDTH);
}

THandleItem *TResizeItem::currentHandleItem() const
{
    return mCurrentHandleItem;
}

void TResizeItem::setCurrentHandleItem(THandleItem *currentHandleItem)
{
    mCurrentHandleItem = currentHandleItem;
}

bool TResizeItem::startResizing()
{
    mCurrentHandleItem = nullptr;
    for(int i=0;i<HA_COUNT;i++) {
        THandleItem *handItem = mHandleItems[i];
        if(handItem->isUnderMouse()) {
            mCurrentHandleItem = handItem;
            break;
        }
    }
    return mCurrentHandleItem;
}

void TResizeItem::endResizing()
{
    mCurrentHandleItem = nullptr;
}

void TResizeItem::slotHandleMoved(const QPointF &offset)
{
    THandleItem *handleItem = dynamic_cast<THandleItem*>(sender());
    if(!handleItem)
        return;

    HandleAnchor anchor = handleItem->anchor();
    qreal dx1 = 0;
    qreal dy1 = 0;
    qreal dx2 = 0;
    qreal dy2 = 0;
    qreal x = offset.x();
    qreal y = offset.y();
    switch (anchor) {
    case HA_LEFT_TOP:
        dx1 = -x;
        dy1 = -y;
        break;
    case HA_TOP_RIGHT:
        dy1 = -y;
        dx2 = x;
        break;
    case HA_LEFT_CENTER:
        dx1 = -x;
        break;
    case HA_RIGHT_CENTER:
        dx2 = x;
        break;
    case HA_LEFT_BOTTOM:
        dx1 = -x;
        dy2 = y;
        break;
    case HA_BOTTOM_CENTER:
        dy2 = y;
        break;
    case HA_BOTTOM_RIGHT:
        dx2 = x;
        dy2 = y;
        break;
    case HA_TOP_CENTER:
        dy1 = -y;
        break;
    case HA_COUNT:
        break;
    }
    emit requestAdjustRect(QMarginsF(dx1, dy1, dx2, dy2));
}

QRectF TResizeItem::boundingRect() const
{
    return mBoundingRect;
}

void TResizeItem::paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *)
{
    //p->drawRect(mBoundingRect);
}
