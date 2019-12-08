#include "object.h"
#include "../../document.h"
#include "../../base/tr.h"
#include "../../base/finddoc.h"

TObject::TObject(Type type, QObject *parent) :
    TPropertyObject(parent)
  , mDocument(nullptr)
  , mType(type)
  , mVisible(true)
{
#ifndef TEST
    FIND_DOCUMENT;
#endif

    initPropertySheet();
}

TObject::Type TObject::type() const
{
    return mType;
}

void TObject::move(const QPointF &)
{

}

void TObject::initPropertySheet()
{

}

bool TObject::visible() const
{
    return mVisible;
}

void TObject::setVisible(bool visible)
{
    mVisible = visible;
}
