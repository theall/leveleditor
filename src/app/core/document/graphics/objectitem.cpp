#include "objectitem.h"

TObjectItem::TObjectItem(TObject *object, QGraphicsItem *parent) :
    QGraphicsObject(parent)
  , mObject(object)
{
    Q_ASSERT(mObject);

    connect(mObject->propertySheet(),
            SIGNAL(propertyItemValueChanged(TPropertyItem*,QVariant)),
            this,
            SLOT(slotPropertyItemValueChanged(TPropertyItem*,QVariant))
            );
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
    if(pid==PID_OBJECT_POS || pid==PID_OBJECT_SIZE) {
        emit boundingRectChanged();
    }

    propertyValueChanged(pid);
}
