#include "rotatehandle.h"

#include <QGraphicsScene>

static QPainterPath createRotateArrow()
{
    const qreal arrowHeadPos = 12;
    const qreal arrowHeadLength = 4.5;
    const qreal arrowHeadWidth = 5;
    const qreal bodyWidth = 1.5;
    const qreal outerArcSize = arrowHeadPos + bodyWidth - arrowHeadLength;
    const qreal innerArcSize = arrowHeadPos - bodyWidth - arrowHeadLength;

    QPainterPath path;
    path.moveTo(arrowHeadPos, 0);
    path.lineTo(arrowHeadPos + arrowHeadWidth, arrowHeadLength);
    path.lineTo(arrowHeadPos + bodyWidth, arrowHeadLength);
    path.arcTo(QRectF(arrowHeadLength - outerArcSize,
                      arrowHeadLength - outerArcSize,
                      outerArcSize * 2,
                      outerArcSize * 2),
               0, -90);
    path.lineTo(arrowHeadLength, arrowHeadPos + arrowHeadWidth);
    path.lineTo(0, arrowHeadPos);
    path.lineTo(arrowHeadLength, arrowHeadPos - arrowHeadWidth);
    path.lineTo(arrowHeadLength, arrowHeadPos - bodyWidth);
    path.arcTo(QRectF(arrowHeadLength - innerArcSize,
                      arrowHeadLength - innerArcSize,
                      innerArcSize * 2,
                      innerArcSize * 2),
               -90, 90);
    path.lineTo(arrowHeadPos - arrowHeadWidth, arrowHeadLength);
    path.closeSubpath();

    return path;
}

TRotateHandle::TRotateHandle(AnchorPosition corner, QGraphicsItem *parent)
    : THandle(parent)
    , mArrowPath(createRotateArrow())
{
    setZValue(10000 + 1);

    QTransform transform;

    switch (corner) {
    case TopLeftAnchor:     transform.rotate(180);  break;
    case TopRightAnchor:    transform.rotate(-90);  break;
    case BottomLeftAnchor:  transform.rotate(90);   break;
    default:                break; // BottomRight
    }

    mArrowPath = transform.map(mArrowPath);
}

TRotateHandle::~TRotateHandle()
{
//        qreal handleRotation = areaItem->rotation();
//        mOriginIndicator->setPos(center);
//        mRotateHandles[TopLeftAnchor]->setPos(topLeft);
//        mRotateHandles[TopRightAnchor]->setPos(topRight);
//        mRotateHandles[BottomLeftAnchor]->setPos(bottomLeft);
//        mRotateHandles[BottomRightAnchor]->setPos(bottomRight);
//        for (TRotateHandle *handle : mRotateHandles)
//            handle->setRotation(handleRotation);
}

QRectF TRotateHandle::boundingRect() const
{
    return mArrowPath.boundingRect().adjusted(-1, -1, 1, 1);
}

void TRotateHandle::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPen pen(mUnderMouse ? Qt::black : Qt::lightGray, 1);
    QColor brush(mUnderMouse ? Qt::white : Qt::black);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawPath(mArrowPath);
}

void TRotateHandle::mouseDragged(const QPointF &distance)
{
    Q_UNUSED(distance);
}

int TRotateHandle::type() const
{
    return GIT_HANDLE_ROTATE;
}


TRotateHandlesManager::TRotateHandlesManager(QGraphicsScene *scene) :
    mParentItem(nullptr)
{
    Q_ASSERT(scene);

    for (int i = 0; i < CornerAnchorCount; ++i)
    {
        mRotateHandles[i] = new TRotateHandle(static_cast<AnchorPosition>(i));
        scene->addItem(mRotateHandles[i]);
    }
}

TRotateHandlesManager::~TRotateHandlesManager()
{
    for (TRotateHandle *handle : mRotateHandles)
        delete handle;
}

QGraphicsItem *TRotateHandlesManager::parentItem() const
{
    return mParentItem;
}

void TRotateHandlesManager::setParentItem(QGraphicsItem *parentItem)
{
    if(mParentItem==parentItem || dynamic_cast<TRotateHandle*>(parentItem))
        return;

    for (int i = 0; i < AnchorCount; ++i) {
        mRotateHandles[i]->setParentItem(parentItem);
    }

    mParentItem = parentItem;
}
