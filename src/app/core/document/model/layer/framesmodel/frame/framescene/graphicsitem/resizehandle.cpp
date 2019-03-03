#include "resizehandle.h"
#include "areagraphicsitem.h"

#include <QGraphicsScene>

static QPainterPath createResizeArrow(bool straight)
{
    const qreal arrowLength = straight ? 6 : 7;
    const qreal arrowHeadLength = 2;
    const qreal arrowHeadWidth = 2.5;
    const qreal bodyWidth = 0.5;

    QPainterPath path;
    path.lineTo(arrowHeadWidth, arrowHeadLength);
    path.lineTo(0 + bodyWidth, arrowHeadLength);
    path.lineTo(0 + bodyWidth, arrowLength - arrowHeadLength);
    path.lineTo(arrowHeadWidth, arrowLength - arrowHeadLength);
    path.lineTo(0, arrowLength);
    path.lineTo(-arrowHeadWidth, arrowLength - arrowHeadLength);
    path.lineTo(0 - bodyWidth, arrowLength - arrowHeadLength);
    path.lineTo(0 - bodyWidth, arrowHeadLength);
    path.lineTo(-arrowHeadWidth, arrowHeadLength);
    path.closeSubpath();
    path.translate(0, straight ? 1 : 1.5);

    return path;
}

static QPainterPath createResizeRect()
{
    QPainterPath path;
    path.addRect(0, 0, 5, 5);
    return path;
}

TResizeHandle::TResizeHandle(AnchorPosition anchorPosition, QGraphicsItem *parent)
    : THandle(parent)
  , mAnchorPosition(anchorPosition)
  , mResizingLimitHorizontal(false)
  , mResizingLimitVertical(false)
  , mUseArrow(true)
{
    setUseArrow(true);

    setZValue(10000 + 1 + (anchorPosition < TopAnchor ? anchorPosition + 1 : 0));

    QTransform transform;

    switch (anchorPosition) {
    case TopLeftAnchor:
        transform.rotate(135);
        break;
    case TopRightAnchor:
        transform.rotate(-135);
        break;
    case BottomLeftAnchor:
        transform.rotate(45);
        break;
    case BottomRightAnchor:
        transform.rotate(-45);
        break;
    case TopAnchor:
        transform.rotate(180);
        mResizingLimitHorizontal = true;
        break;
    case LeftAnchor:
        transform.rotate(90);
        mResizingLimitVertical = true;
        break;
    case RightAnchor:
        transform.rotate(-90);
        mResizingLimitVertical = true;
        break;
    case BottomAnchor:
    default:
        mResizingLimitHorizontal = true;
        break;
    }

    mArrowPath = transform.map(mArrowPath);
}

TResizeHandle::~TResizeHandle()
{

}

AnchorPosition TResizeHandle::anchorPosition() const
{
    return mAnchorPosition;
}

void TResizeHandle::setResizingOrigin(const QPointF &resizingOrigin)
{
    mResizingOrigin = resizingOrigin;
}

void TResizeHandle::setPosResizingOrigin(const QPointF &pos, const QPointF &resizingOrigin)
{
    setPos(pos);
    mResizingOrigin = resizingOrigin;
}

QPointF TResizeHandle::resizingOrigin() const
{
    return mResizingOrigin;
}

bool TResizeHandle::resizingLimitHorizontal() const
{
    return mResizingLimitHorizontal;
}

bool TResizeHandle::resizingLimitVertical() const
{
    return mResizingLimitVertical;
}

QRectF TResizeHandle::boundingRect() const
{
    return mArrowPath.boundingRect().adjusted(-1, -1, 1, 1);
}

void TResizeHandle::slotParentAreaChanged(const QRectF &rect)
{
    QPointF topLeft = rect.topLeft();
    QPointF topRight = rect.topRight();
    QPointF bottomLeft = rect.bottomLeft();
    QPointF bottomRight = rect.bottomRight();
    QPointF top = (topLeft + topRight) / 2;
    QPointF left = (topLeft + bottomLeft) / 2;
    QPointF right = (topRight + bottomRight) / 2;
    QPointF bottom = (bottomLeft + bottomRight) / 2;
    switch (mAnchorPosition) {
    case TopLeftAnchor:
        setPos(topLeft);
        break;
    case TopRightAnchor:
        setPos(topRight);
        break;
    case BottomLeftAnchor:
        setPos(bottomLeft);
        break;
    case BottomRightAnchor:
        setPos(bottomRight);
        break;
    case TopAnchor:
        setPos(top);
        break;
    case LeftAnchor:
        setPos(left);
        break;
    case RightAnchor:
        setPos(right);
        break;
    case BottomAnchor:
        setPos(bottom);
        break;
    default:
        break;
    }
}

void TResizeHandle::setUseArrow(bool useArrow)
{
    mArrowPath = useArrow?createResizeArrow(mAnchorPosition>BottomRightAnchor):createResizeRect();
    mUseArrow = useArrow;
    update();
}

void TResizeHandle::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPen pen(mUnderMouse ? Qt::black : Qt::lightGray, 1);
    QColor brush(mUnderMouse ? Qt::white : Qt::black);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawPath(mArrowPath);
}

QVariant TResizeHandle::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if(change==ItemParentChange) {
        if(TAreaGraphicsItem *oldParentItem = dynamic_cast<TAreaGraphicsItem*>(parentItem()))
        {
            oldParentItem->disconnect(this);
        }
        TAreaGraphicsItem *newParentItem = dynamic_cast<TAreaGraphicsItem*>(value.value<QGraphicsItem*>());
        if(newParentItem)
        {
            connect(newParentItem,
                    SIGNAL(areaChanged(QRectF)),
                    this,
                    SLOT(slotParentAreaChanged(QRectF)));
            slotParentAreaChanged(newParentItem->boundingRect());
        }
        mParentLastRect = QRectF();
    }
    return THandle::itemChange(change, value);
}

void TResizeHandle::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    THandle::hoverEnterEvent(event);
}

void TResizeHandle::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    THandle::hoverLeaveEvent(event);
}

void TResizeHandle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    THandle::mousePressEvent(event);

    if(TAreaGraphicsItem *currentParentItem = dynamic_cast<TAreaGraphicsItem*>(parentItem()))
    {
        mParentLastRect = currentParentItem->boundingRect();
    } else {
        mParentLastRect = QRectF();
    }
}

void TResizeHandle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    THandle::mouseMoveEvent(event);
}

void TResizeHandle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    THandle::mouseReleaseEvent(event);
}

void TResizeHandle::mouseDragged(const QPointF &distance)
{
    TAreaGraphicsItem *currentParentItem = dynamic_cast<TAreaGraphicsItem*>(parentItem());
    if(!currentParentItem)
        return;

    QRectF newRect = mParentLastRect;
    if(newRect.isEmpty())
        newRect = currentParentItem->boundingRect();

    qreal dx1 = 0;
    qreal dy1 = 0;
    qreal dx2 = 0;
    qreal dy2 = 0;
    qreal w = newRect.width();
    qreal h = newRect.height();
    switch (mAnchorPosition) {
    case TopLeftAnchor:
        dx1 = qMin(distance.x(), w);
        dy1 = qMin(distance.y(), h);
        break;
    case TopRightAnchor:
        dx2 = qMax(distance.x(), -w);
        dy1 = qMin(distance.y(), h);
        break;
    case BottomLeftAnchor:
        dx1 = qMin(distance.x(), w);
        dy2 = qMax(distance.y(), -h);
        break;
    case BottomRightAnchor:
        dx2 = qMax(distance.x(), -w);
        dy2 = qMax(distance.y(), -h);
        break;
    case TopAnchor:
        dy1 = qMin(distance.y(), h);
        break;
    case LeftAnchor:
        dx1 = qMin(distance.x(), w);
        break;
    case RightAnchor:
        dx2 = qMax(distance.x(), -w);
        break;
    case BottomAnchor:
        dy2 = qMax(distance.y(), -h);
        break;
    default:
        break;
    }
    newRect.adjust(dx1, dy1, dx2, dy2);
    currentParentItem->cmdSetRect(newRect);
}

int TResizeHandle::type() const
{
    return GIT_HANDLE_RESIZE;
}

TResizeHandlesManager::TResizeHandlesManager(QGraphicsScene *scene) :
    mParentItem(nullptr)
{
    Q_ASSERT(scene);

    for (int i = 0; i < AnchorCount; ++i) {
        mResizeHandles[i] = new TResizeHandle(static_cast<AnchorPosition>(i));
        scene->addItem(mResizeHandles[i]);
    }
}

TResizeHandlesManager::~TResizeHandlesManager()
{
    for (TResizeHandle *handle : mResizeHandles)
        delete handle;
}

QGraphicsItem *TResizeHandlesManager::parentItem() const
{
    return mParentItem;
}

void TResizeHandlesManager::setParentItem(QGraphicsItem *parentItem)
{
    if(mParentItem==parentItem || dynamic_cast<TResizeHandle*>(parentItem))
        return;

    for (int i = 0; i < AnchorCount; ++i) {
        mResizeHandles[i]->setParentItem(parentItem);
    }

    mParentItem = parentItem;
}
