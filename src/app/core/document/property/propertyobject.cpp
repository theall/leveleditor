#include "propertyobject.h"

TPropertyObject::TPropertyObject(QObject *parent) :
    QObject(parent)
  , mPropertySheet(new TPropertySheet(this))
{
}

TPropertyObject::~TPropertyObject()
{

}

TPropertySheet *TPropertyObject::propertySheet() const
{
    return mPropertySheet;
}

TPropertyItems TPropertyObject::propertyItems() const
{
    return mPropertySheet->propertyList();
}

