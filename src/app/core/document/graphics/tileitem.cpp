#include "tileitem.h"

#include <QCursor>
#include <QGraphicsSceneMouseEvent>

const qreal GAP = 4.0;

TStartPointItem::TStartPointItem(TDoorItem *doorItem) :
    TObjectItem(doorItem->startPoint(), doorItem)
  , mStartPoint(doorItem->startPoint())
{
    Q_ASSERT(mStartPoint);

    updateBoundingRect();
}

TStartPointItem::~TStartPointItem()
{

}

void TStartPointItem::updateBoundingRect()
{
    QPointF _pos = mStartPoint->getValue(PID_OBJECT_POS).toPointF();
    mBoundingRect.setSize(QSize(20,30));
    mBoundingRect.moveTop(_pos.y()-mBoundingRect.height());
    mBoundingRect.moveLeft(_pos.x()-mBoundingRect.width()/2);
}

QRectF TStartPointItem::boundingRect() const
{
    return mBoundingRect;
}

void TStartPointItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    const qreal lineWidth = 1.0;
    const qreal shadowDist = lineWidth;
    const QPointF shadowOffset = QPointF(shadowDist * 0.5,
                                         shadowDist * 0.5);

    QPen linePen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    linePen.setCosmetic(true);
    QPen shadowPen(linePen);
    shadowPen.setColor(Qt::black);

    QColor brushColor = Qt::gray;
    brushColor.setAlpha(50);
    const QBrush fillBrush(brushColor);
    painter->setPen(Qt::NoPen);
    painter->setBrush(fillBrush);

    QPainterPath path;
    painter->translate(mBoundingRect.topLeft());
    const qreal radius = 10.0;
    const qreal sweep = 235.0;
    const qreal startAngle = 90.0 - sweep / 2;
    QRectF rectangle(0, 0, radius*2, radius*2);
    path.moveTo(radius+radius*cos(startAngle*M_PI/180.0), radius-radius*sin(startAngle*M_PI/180.0));
    path.arcTo(rectangle, startAngle, sweep);
    path.lineTo(radius, 3*radius);
    path.closeSubpath();

    painter->setPen(shadowPen);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(path.translated(shadowOffset));
    painter->setPen(linePen);
    painter->setBrush(fillBrush);
    painter->drawPath(path);

    const QBrush opaqueBrush(Qt::gray);
    painter->setBrush(opaqueBrush);
    const qreal smallRadius = radius / 4.0;
    painter->drawEllipse(radius-smallRadius, radius-smallRadius, smallRadius * 2, smallRadius * 2);
}

void TStartPointItem::propertyValueChanged(PropertyID pid)
{
    if(pid == PID_OBJECT_POS)
        updateBoundingRect();
}

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
        mFollowTileTrackItem = new TTrackItem(this, mFollowTileItem);
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

QRectF TDoorItem::boundingRect() const
{
    return mBoundingRect;
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
    QPen pen(gray, 2, Qt::DotLine);
    pen.setCosmetic(true);
    painter->setPen(pen);
    painter->drawLine(trackLine);
}

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

TRandomRegionItem::TRandomRegionItem(TDoorItem *doorItem) :
    TObjectItem(nullptr, doorItem)
{

}

QRectF TRandomRegionItem::boundingRect() const
{

}

void TRandomRegionItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

void TRandomRegionItem::propertyValueChanged(PropertyID pid)
{

}
