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
        int type,
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
        int ret = mPropertyMap.remove(propertyItem->name());
        if(ret == 1)
        {
            itemsRemoved.append(propertyItem);
        }
    }
    if(itemsRemoved.size() > 0)
        emit propertyItemsRemoved(itemsRemoved);
}

QVariant TPropertySheet::getValue(const QString &name)
{
    TPropertyItem *item = mPropertyMap.value(name, nullptr);
    if(item)
        return item->value();
    return QVariant();
}

void TPropertySheet::setValue(const QString &name, const QVariant &value)
{
    TPropertyItem *item = mPropertyMap.value(name, nullptr);
    if(item)
        item->setValue(value);
}

TPropertyItem *TPropertySheet::operator [](const QString &name)
{
    return mPropertyMap.value(name, nullptr);
}

TPropertyItem *TPropertySheet::get(const QString &name)
{
    return mPropertyMap.value(name, nullptr);
}

void TPropertySheet::clear()
{
    mPropertyMap.clear();
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
        if(!beforeProperty)
            mPropertyMap.insert(propertyItem->name(), propertyItem);
        else {
            QMap<QString, TPropertyItem*>::iterator findIt = mPropertyMap.end();
            for(QMap<QString, TPropertyItem*>::iterator it=mPropertyMap.begin();it!=mPropertyMap.end();it++)
            {
                if(it.value() == beforeProperty)
                {
                    findIt = it;
                    break;
                }
            }
            mPropertyMap.insert(findIt, propertyItem->name(), propertyItem);
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
