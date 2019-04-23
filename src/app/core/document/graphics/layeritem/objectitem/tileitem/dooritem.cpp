#include "dooritem.h"
#include "startpointitem.h"
#include "randomregionitem.h"
#include "../tileitem.h"
#include <QCursor>

const qreal GAP = 4.0;

TDoorItem::TDoorItem(TTileItem *tileItem) :
    TObjectItem(tileItem->door(), tileItem)
  , mDoor(tileItem->door())
  , mMouseRegion(OUT)
  , mLeftButtonDown(false)
  , mResizeHovered(false)
  , mStartPointItem(nullptr)
  , mDoorStartPointTrackItem(nullptr)
  , mFollowTileTrackItem(nullptr)
{
    Q_ASSERT(mDoor);

    setAutonomy(true);
    updateBoundingRect();

    TDoor::Type doorType = mDoor->type();
    if(doorType == TDoor::Recycle) {
        mStartPointItem = new TStartPointItem(this);
        mDoorStartPointTrackItem = new TTrackItem(this, mStartPointItem);
    } else if(doorType == TDoor::Random) {
        mRandomRegionItem = new TRandomRegionItem(this);
    } else if(doorType == TDoor::Follow) {
        //mFollowTileTrackItem = new TTrackItem(this, mFollowTileItem);
    }
}

TDoorItem::~TDoorItem()
{
    if(mStartPointItem)
        delete mStartPointItem;
    if(mDoorStartPointTrackItem)
        delete mDoorStartPointTrackItem;
}

TStartPoint *TDoorItem::startPoint() const
{
    return mDoor->startPoint();
}

void TDoorItem::updateBoundingRect()
{
    mRealRect = mDoor->rect();
    mBoundingRect = mRealRect.adjusted(-GAP, -GAP, GAP, GAP);
    mIsVertical = mDoor->dir()==TDoor::Vertical;
    update();
}

TDoorItem::MouseRegion TDoorItem::checkMouseRegion(const QPointF &pos)
{
    qreal top = mBoundingRect.top();
    qreal left = mBoundingRect.left();
    qreal right = mBoundingRect.right();
    qreal bottom = mBoundingRect.bottom();
    QRectF targetRect1;
    QRectF targetRect2;
    if(mIsVertical) {
        QSizeF targetSize;
        targetSize.setWidth(mBoundingRect.width());
        targetSize.setHeight(GAP*4);
        targetRect1.setTopLeft(QPointF(top-GAP, left));
        targetRect1.setSize(targetSize);
        targetRect2.setTopLeft(QPointF(bottom-GAP, left));
        targetRect2.setSize(targetSize);
    } else {
        QSizeF targetSize;
        targetSize.setWidth(GAP*2);
        targetSize.setHeight(mBoundingRect.height());
        targetRect1.setTopLeft(QPointF(left-GAP, top));
        targetRect1.setSize(targetSize);
        targetRect2.setTopLeft(QPointF(right-GAP, top));
        targetRect2.setSize(targetSize);
    }
    if(targetRect1.contains(pos))
        return LEFT;
    else if(targetRect2.contains(pos))
        return RIGHT;
    else if(mBoundingRect.contains(pos))
        return BLANK;
    return OUT;
}

void TDoorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QLineF line1;
    QLineF line2;
    QColor color1(Qt::gray);
    QColor color2(Qt::gray);
    if(mMouseRegion==BLANK || mMouseRegion==LEFT) {
        color1 = QColor(Qt::red);
    }
    if(mMouseRegion==BLANK || mMouseRegion==RIGHT) {
        color2 = QColor(Qt::red);
    }
    QPen pen1(color1, 2, Qt::SolidLine);
    QPen pen2(color2, 2, Qt::SolidLine);
    pen1.setCosmetic(true);
    pen2.setCosmetic(true);

    if(mIsVertical) {
        line1.setPoints(mRealRect.topLeft(), mRealRect.topRight());
        line2.setPoints(mRealRect.bottomLeft(), mRealRect.bottomRight());
    } else {
        line1.setPoints(mRealRect.topLeft(), mRealRect.bottomLeft());
        line2.setPoints(mRealRect.topRight(), mRealRect.bottomRight());
    }

    painter->setPen(pen1);
    painter->drawLine(line1);

    painter->setPen(pen2);
    painter->drawLine(line2);

    if(!mMovingPos.isNull()) {
        QPen pen(Qt::gray, 2, Qt::DotLine);
        painter->setPen(pen);

        QPointF p1, p2;
        if(mIsVertical) {
            p1.setX(mRealRect.left());
            p1.setY(mMovingPos.y());
            p2.setX(mRealRect.right());
            p2.setY(mMovingPos.y());
        } else {
            p1.setX(mMovingPos.x());
            p1.setY(mRealRect.top());
            p2.setX(mMovingPos.x());
            p2.setY(mRealRect.bottom());
        }
        painter->drawLine(p1, p2);
    }
    if(!mMovingRect.isNull()) {
        QPen pen(Qt::black, 1, Qt::DotLine);
        painter->setPen(pen);
        painter->drawRect(mMovingRect);
    }
}

void TDoorItem::propertyValueChanged(PropertyID pid)
{
    if(pid==PID_OBJECT_POS || pid==PID_OBJECT_SIZE) {
        updateBoundingRect();
    }
}

void TDoorItem::mousePressed(QGraphicsSceneMouseEvent *event)
{
    QPointF mousePos = event->scenePos();
    mMouseRegion = checkMouseRegion(mousePos);
    if(event->button() == Qt::LeftButton) {
        mLeftButtonDown = true;
        mLeftButtonDownPos = mousePos;
        setNeedGrabMouse(true);
    } else {
        mLeftButtonDown = false;
        setNeedGrabMouse(false);
    }
    event->accept();
}

void TDoorItem::mouseMoved(QGraphicsSceneMouseEvent *event)
{
    event->accept();
    QPointF mousePos = event->scenePos();
    if(mLeftButtonDown) {
        if(mMouseRegion==RIGHT || mMouseRegion==LEFT) {
            mMovingPos = event->scenePos();
            if(mIsVertical) {
                qreal top = mRealRect.top() + GAP;
                qreal bottom = mRealRect.bottom() - GAP;
                qreal y = mMovingPos.y();
                if(mMouseRegion==RIGHT && y<top)
                    y = top;
                if(mMouseRegion==LEFT && y>bottom)
                    y = bottom;
                mMovingPos.setY(y);
            } else {
                qreal left = mRealRect.left() + GAP;
                qreal right = mRealRect.right() - GAP;
                qreal x = mMovingPos.x();
                if(mMouseRegion==RIGHT && x<left)
                    x = left;
                if(mMouseRegion==LEFT && x>right)
                    x = right;
                mMovingPos.setX(x);
            }
        } else if(mMouseRegion == BLANK) {
            mMovingRect = mRealRect;
            QPointF offset = event->scenePos() - mLeftButtonDownPos;
            if(mIsVertical) {
                offset.setX(0);
            } else {
                offset.setY(0);
            }
            mMovingRect.moveTo(mMovingRect.topLeft()+offset);
        }
    } else {
        mMouseRegion = checkMouseRegion(mousePos);
        mResizeHovered = mMouseRegion!=BLANK;
        if(mResizeHovered)
            setCursor(Qt::SizeHorCursor);
        else
            setCursor(Qt::ArrowCursor);
        if(mRealRect.contains(mousePos)) {
            setNeedGrabMouse(true);
        } else {
            setNeedGrabMouse(false);
            mMouseRegion = OUT;
        }
    }
    updateBoundingRect();
}

void TDoorItem::mouseReleased(QGraphicsSceneMouseEvent *event)
{
    QPointF offset = mMovingPos - mLeftButtonDownPos;
    qreal dx = 0;
    switch (mMouseRegion) {
    case LEFT:
        if(mIsVertical) {
            dx = offset.y();
        } else {
            dx = offset.x();
        }
        mDoor->move(dx, TDoor::Left);
        break;
    case RIGHT:
        if(mIsVertical) {
            dx = offset.y();
        } else {
            dx = offset.x();
        }
        mDoor->move(dx, TDoor::Right);
        break;
    case BLANK:
        offset = mMovingRect.topLeft() - mRealRect.topLeft();
        if(mIsVertical) {
            dx = offset.y();
        } else {
            dx = offset.x();
        }
        mDoor->move(dx, TDoor::LeftRight);
        break;
    case OUT:
        break;
    }
    mMovingPos = QPointF();
    mMovingRect = QRectF();
    mLeftButtonDown = false;
    updateBoundingRect();
    event->accept();
}
