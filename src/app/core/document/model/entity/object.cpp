#include "object.h"

TObject::TObject(Type type, QObject *parent) :
    TPropertyObject(parent)
  , mType(type)
{

}

TObject::Type TObject::type() const
{
    return mType;
}
