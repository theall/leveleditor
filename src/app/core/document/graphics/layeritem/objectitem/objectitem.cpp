#include "objectitem.h"

#include <QPen>
#include <QDebug>
#include <QPainter>

QMap<TObject*, TObjectItem*> TObjectItem::mObjectItemMap;

TObjectItem::TObjectItem(TObject *object, QGraphicsItem *parent) :
    QGraphicsObject(parent)
  , mObject(object)
  , mAutonomy(false)
  , mNeedGrabMouse(false)
  , mDrawBorder(true)
  , mBorderColor(Qt::black)
{
    Q_ASSERT(mObject);

    setBoundingRect(mObject->rect());
    connect(mObject->propertySheet(),
            SIGNAL(propertyItemValueChanged(TPropertyItem*,QVariant)),
            this,
            SLOT(slotPropertyItemValueChanged(TPropertyItem*,QVariant))
            );

    setToolTip(mObject->toString());
    mObjectItemMap.insert(mObject, this);
}

TObjectItem::~TObjectItem()
{

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

TObjectItem *TObjectItem::getObjectItem(TObject *object)
{
    return mObjectItemMap[object];
}

void TObjectItem::slotPropertyItemValueChanged(TPropertyItem *item, const QVariant &)
{
    PropertyID pid = item->propertyId();

    // The inheired class may update bounding rect in propertyValueChanged
    propertyValueChanged(pid);

    // Notify to selection item and hovering item
    if(pid==PID_OBJECT_RECT) {
        mBoundingRect = item->value().toRectF();

//        static int i = 0;
//        qDebug() << i << "Bounding changed";
//        i++;
        emit boundingRectChanged(mBoundingRect);
    }
}

void TObjectItem::setBoundingRect(const QRectF &boundingRect)
{
    mBoundingRect = boundingRect;
}

void TObjectItem::step()
{

}

bool TObjectItem::drawBorder() const
{
    return mDrawBorder;
}

void TObjectItem::setDrawBorder(bool drawBorder)
{
    mDrawBorder = drawBorder;
}

QColor TObjectItem::borderColor() const
{
    return mBorderColor;
}

void TObjectItem::setBorderColor(const QColor &borderColor)
{
    if(mBorderColor == borderColor)
        return;

    mBorderColor = borderColor;
    update(mBoundingRect);
}

QRectF TObjectItem::boundingRect() const
{
    return mBoundingRect;
}

void TObjectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if(mDrawBorder) {
        QPen pen(mBorderColor);
        painter->setPen(pen);
        painter->drawRect(mBoundingRect);
    }
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
