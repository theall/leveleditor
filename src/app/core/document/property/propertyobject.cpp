#include "propertyobject.h"

TPropertyObject::TPropertyObject(QObject *parent) :
    QObject(parent)
  , mPropertySheet(new TPropertySheet(this))
{
}

TPropertyObject::~TPropertyObject()
{
    delete mPropertySheet;
}

TPropertySheet *TPropertyObject::propertySheet() const
{
    return mPropertySheet;
}

TPropertyItems TPropertyObject::propertyItems() const
{
    return mPropertySheet->propertyList();
}

QVariant TPropertyObject::getValue(const QString &name) const
{
    return mPropertySheet->getValue(name);
}

void TPropertyObject::setValue(const QString &name, const QVariant &value)
{
    mPropertySheet->setValue(name, value);
}

TPropertyItem *TPropertyObject::operator [](const QString &name) const
{
    return mPropertySheet->get(name);
}

TPropertyItem *TPropertyObject::get(const QString &name) const
{
    return mPropertySheet->get(name);
}

QVariant TPropertyObject::getValue(const PropertyID &pid) const
{
    return mPropertySheet->getValue(pid);
}

void TPropertyObject::setValue(const PropertyID &pid, const QVariant &value)
{
    setValue(pid, value);
}

TPropertyItem *TPropertyObject::operator [](const PropertyID &pid) const
{
    return mPropertySheet->get(pid);
}

TPropertyItem *TPropertyObject::get(const PropertyID &pid) const
{
    return mPropertySheet->get(pid);
}
