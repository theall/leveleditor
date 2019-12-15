#include "object.h"
#include "../../document.h"
#include "../../base/tr.h"
#include "../../base/finddoc.h"

const QString g_type_string[TObject::INVALID+1] = {
    T("Area"),
    T("Darea"),
    T("Box"),
    T("Plat"),
    T("Tile"),
    T("Wall"),
    T("Point"),
    T("Door"),
    T("Frame"),
    T("Animation"),
    T("Enemy"),
    T("Trigger"),
    T("Invalid")
};

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
    mPropertySheet->setContextName(g_type_string[mType]);
}

bool TObject::visible() const
{
    return mVisible;
}

void TObject::setVisible(bool visible)
{
    mVisible = visible;
}
