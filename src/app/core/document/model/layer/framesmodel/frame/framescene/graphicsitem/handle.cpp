#include "handle.h"

#include <QGraphicsSceneMouseEvent>

THandle::THandle(QGraphicsItem *parent, bool visibility) :
    QGraphicsObject(parent)
  , mUnderMouse(false)
  , mMousePressed(false)
{
    setFlags(QGraphicsItem::ItemIsMovable |
             QGraphicsItem::ItemIgnoresTransformations |
             QGraphicsItem::ItemIgnoresParentOpacity);
    setAcceptHoverEvents(true);
    setCursor(Qt::ArrowCursor);
    setVisible(visibility);
}

THandle::~THandle()
{

}

void THandle::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    mUnderMouse = true;
    update();
}

void THandle::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    mUnderMouse = false;
    update();
}

void THandle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    mMousePressed = true;
    mMousePressedPos = event->scenePos();
}

void THandle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(mMousePressed)
        mouseDragged(event->scenePos()-mMousePressedPos);
}

void THandle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);

    mMousePressed = false;
    mMousePressedPos = QPointF();
}

QVariant THandle::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemVisibleHasChanged && value.toBool()) {
        if (mUnderMouse)
            mUnderMouse = isUnderMouse();
    } else if(change==ItemParentHasChanged) {
        setVisible(value.value<QGraphicsItem*>()!=nullptr);
    }
    return QGraphicsObject::itemChange(change, value);
}
