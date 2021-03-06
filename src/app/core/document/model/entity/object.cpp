#include "object.h"
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
  , mType(type)
  , mVisible(true)
{
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

void TObject::saveToStream(QDataStream &stream) const
{

}

void TObject::readFromStream(QDataStream &stream)
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

QByteArray TObject::toByteArray(TObject *object) const
{

}

void TObject::loadFromByteArray(const QByteArray &byteArray)
{

}

void TObject::setPos(const QPointF &pos)
{

}
