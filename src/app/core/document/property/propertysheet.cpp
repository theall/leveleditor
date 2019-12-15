#include "propertysheet.h"

TPropertySheet::TPropertySheet(QObject *parent) :
    QObject(parent)
{

}

TPropertySheet::~TPropertySheet()
{

}

TPropertyItems TPropertySheet::propertyList() const
{
    return mPropertyMap.values();
}

TPropertyItem *TPropertySheet::addProperty(
        PropertyType type,
        const QString &name,
        PropertyID undoCommand,
        const QVariant &value,
        TPropertyItem *parent,
        TPropertyItem *beforeProperty)
{
    TPropertyItem *item = new TPropertyItem(type, name, undoCommand, this);
    item->setValue(value);
    addProperty(item, parent, beforeProperty);
    return item;
}

TPropertyItem *TPropertySheet::addGroupProperty(
        const QString &name,
        TPropertyItem *parent,
        TPropertyItem *beforeProperty)
{
    TPropertyItem *item = new TPropertyItem(PT_GROUP, name, this);
    addProperty(item, parent, beforeProperty);
    return item;
}

void TPropertySheet::removeProperty(TPropertyItem *propertyItem)
{
    if(!propertyItem)
        return;

    TPropertyItems propertyItemList;
    propertyItemList.append(propertyItem);
    removeProperty(propertyItemList);
}

void TPropertySheet::removeProperty(const TPropertyItems &propertyItemList)
{
    TPropertyItems itemsRemoved;
    for(TPropertyItem *propertyItem : propertyItemList)
    {
        int ret1 = mPropertyMap.remove(propertyItem->name());
        int ret2 = mPropertyIdMap.remove(propertyItem->propertyId());
        if(ret1==1 && ret2==1)
        {
            itemsRemoved.append(propertyItem);
        }
    }
    if(itemsRemoved.size() > 0)
        emit propertyItemsRemoved(itemsRemoved);
}

QVariant TPropertySheet::getValue(const QString &name) const
{
    TPropertyItem *item = mPropertyMap.value(name, nullptr);
    if(item)
        return item->value();
    return QVariant();
}

void TPropertySheet::setValue(const QString &name, const QVariant &value, bool emitSignal)
{
    TPropertyItem *item = mPropertyMap.value(name, nullptr);
    if(item)
        item->setValue(value, emitSignal);
}

TPropertyItem *TPropertySheet::operator [](const QString &name) const
{
    return mPropertyMap.value(name, nullptr);
}

TPropertyItem *TPropertySheet::get(const QString &name) const
{
    return mPropertyMap.value(name, nullptr);
}

QVariant TPropertySheet::getValue(const PropertyID &pid) const
{
    TPropertyItem *item = mPropertyIdMap.value(pid, nullptr);
    if(item)
        return item->value();
    return QVariant();
}

void TPropertySheet::setValue(const PropertyID &pid, const QVariant &value, bool emitSignal)
{
    TPropertyItem *item = mPropertyIdMap.value(pid, nullptr);
    if(item)
        item->setValue(value, emitSignal);
}

TPropertyItem *TPropertySheet::operator [](const PropertyID &pid) const
{
    return mPropertyIdMap.value(pid, nullptr);
}

TPropertyItem *TPropertySheet::get(const PropertyID &pid) const
{
    return mPropertyIdMap.value(pid, nullptr);
}

void TPropertySheet::setNewValue(const PropertyID &pid, const QVariant &value)
{
    TPropertyItem *item = mPropertyIdMap.value(pid, nullptr);
    if(item)
        item->setNewValue(value);
}

void TPropertySheet::clear()
{
    mPropertyMap.clear();
    mPropertyIdMap.clear();
}

QString TPropertySheet::getContextName()
{
    if(mContextName.isEmpty())
    {
        QObject *o = parent();
        while(o)
        {
            if(!o->objectName().isEmpty())
            {
                mContextName.prepend(o->objectName());
                mContextName.prepend(":");
            }
            o = o->parent();
        }
        if(!mContextName.isEmpty())
            mContextName.remove(0, 1);
    }

    return mContextName;
}

void TPropertySheet::setContextName(const QString &contextName)
{
    mContextName = contextName;
}

QStringList TPropertySheet::names() const
{
    return mPropertyMap.keys();
}

void TPropertySheet::internalAddProperty(TPropertyItem *propertyItem, TPropertyItem *parent, TPropertyItem *beforeProperty)
{
    if(!propertyItem)
        return;

    connect(propertyItem,
            SIGNAL(valueChanged(QVariant,QVariant)),
            this,
            SLOT(slotPropertyItemValueChanged(QVariant,QVariant)));

    if(parent && mPropertyMap.values().contains(parent))
    {
        parent->addSubPropertyItem(propertyItem);
    } else {
        if(!beforeProperty) {
            mPropertyMap.insert(propertyItem->name(), propertyItem);
            mPropertyIdMap.insert(propertyItem->propertyId(), propertyItem);
        } else {
            QMap<QString, TPropertyItem*>::iterator findIt = mPropertyMap.end();
            QMap<PropertyID, TPropertyItem*>::iterator findIt2 = mPropertyIdMap.end();
            QMap<QString, TPropertyItem*>::iterator it;
            QMap<PropertyID, TPropertyItem*>::iterator it2;
            for(it=mPropertyMap.begin(),it2=mPropertyIdMap.begin();it!=mPropertyMap.end();it++,it2++)
            {
                if(it.value() == beforeProperty)
                {
                    findIt = it;
                    findIt2 = it2;
                    break;
                }
            }
            mPropertyMap.insert(findIt, propertyItem->name(), propertyItem);
            mPropertyIdMap.insert(findIt2, propertyItem->propertyId(), propertyItem);
        }
    }
}

void TPropertySheet::slotPropertyItemValueChanged(const QVariant &oldValue, const QVariant &newValue)
{
    Q_UNUSED(newValue);

    TPropertyItem *item = dynamic_cast<TPropertyItem*>(sender());
    emit propertyItemValueChanged(item, oldValue);
}

void TPropertySheet::addProperty(TPropertyItem *propertyItem, TPropertyItem *parent, TPropertyItem *beforeProperty)
{
    TPropertyItems propertyItemList;
    propertyItemList.append(propertyItem);
    addProperty(propertyItemList, parent, beforeProperty);
}

void TPropertySheet::addProperty(const TPropertyItems &propertyItemList, TPropertyItem *parent, TPropertyItem *beforeProperty)
{
    for(TPropertyItem *propertyItem : propertyItemList)
    {
        internalAddProperty(propertyItem, parent, beforeProperty);
    }
    emit propertyItemsAdded(propertyItemList, parent);
}
