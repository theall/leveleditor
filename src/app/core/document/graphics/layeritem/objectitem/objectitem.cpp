#include "objectitem.h"

TObjectItem::TObjectItem(TObject *object, QGraphicsItem *parent) :
    QGraphicsObject(parent)
  , mObject(object)
  , mAutonomy(false)
  , mNeedGrabMouse(false)
{
    Q_ASSERT(mObject);

    connect(mObject->propertySheet(),
            SIGNAL(propertyItemValueChanged(TPropertyItem*,QVariant)),
            this,
            SLOT(slotPropertyItemValueChanged(TPropertyItem*,QVariant))
            );

    setToolTip(object->toString());
}

int TObjectItem::type() const
{
    return Type;
}

TObject *TObjectItem::object() const
{
    return mObject;
}

TObject::Type TObjectItem::objectType() const
{
    return mObject->type();
}

bool TObjectItem::isCongener(TObjectItem *objectItem) const
{
    if(!objectItem)
        return false;

    return mObject->isCongener(objectItem->object());
}

void TObjectItem::slotPropertyItemValueChanged(TPropertyItem *item, const QVariant &)
{
    PropertyID pid = item->propertyId();

    // The inheired class may update bounding rect in propertyValueChanged
    propertyValueChanged(pid);

    // Notify to selection item or hovering item
    if(pid==PID_OBJECT_POS || pid==PID_OBJECT_SIZE) {
        emit boundingRectChanged();
    }
}

QRectF TObjectItem::boundingRect() const
{
    return mBoundingRect;
}

void TObjectItem::paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *)
{

}

bool TObjectItem::needGrabMouse() const
{
    return mNeedGrabMouse;
}

void TObjectItem::setNeedGrabMouse(bool needGrabMouse)
{
    mNeedGrabMouse = needGrabMouse;
}

void TObjectItem::mousePressed(QGraphicsSceneMouseEvent *event)
{
    event->accept();
}

void TObjectItem::mouseMoved(QGraphicsSceneMouseEvent *event)
{
    event->accept();
}

void TObjectItem::mouseReleased(QGraphicsSceneMouseEvent *event)
{
    event->accept();
}

bool TObjectItem::autonomy() const
{
    return mAutonomy;
}

void TObjectItem::setAutonomy(bool autonomy)
{
    mAutonomy = autonomy;
}
