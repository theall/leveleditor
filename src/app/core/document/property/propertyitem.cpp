#include "propertyitem.h"
#include "../document.h"
#include "../base/finddoc.h"
#include "../undocommand/propertyundocommand.h"

const char *g_propertyAttrMap[PA_COUNT] = {
    "constraint",// PA_CONSTRAINT
    "singleStep",// PA_SINGLE_STEP
    "decimals",// PA_DECIMALS
    "enumIcons",// PA_ENUM_ICONS
    "enumNames",// PA_ENUM_NAMES
    "flagNames",// PA_FLAGNAMES
    "maximum",// PA_MAXIMUM
    "minimum",// PA_MINIMUM
    "regExp",// PA_REGEXP
    "echoMode",// PA_ECHO_MODE
    "readOnly",// PA_READ_ONLY
    "textVisible"// PA_TEXT_VISIBLE
};

TPropertyItem::TPropertyItem(
        int type,
        const QString &name,
        PropertyID undoCommand,
        QObject *parent) :
    QObject(parent)
  , mType(type)
  , mName(name)
  , mPropertyId(undoCommand)
  , mDocument(nullptr)
{
    FIND_DOCUMENT;
}

TPropertyItem::~TPropertyItem()
{

}

int TPropertyItem::type() const
{
    return mType;
}

void TPropertyItem::setType(int type)
{
    mType = type;
}

QString TPropertyItem::name() const
{
    return mName;
}

void TPropertyItem::setName(const QString &name)
{
    mName = name;
}

QMap<QString, QVariant> TPropertyItem::attributes() const
{
    return mAttributes;
}

void TPropertyItem::setAttributes(const QMap<QString, QVariant> &attributes)
{
    mAttributes = attributes;
}

void TPropertyItem::setAttributes(const QMap<PropertyAttribute, QVariant> &attributes)
{
    QMap<QString, QVariant> strAttrMap;
    for(PropertyAttribute p : attributes.keys())
    {
        strAttrMap.insert(g_propertyAttrMap[p], attributes[p]);
    }
    mAttributes = strAttrMap;
}

void TPropertyItem::setAttribute(const QString &name, const QVariant &value)
{
    mAttributes[name] = value;
}

void TPropertyItem::setAttribute(const PropertyAttribute &attribute, const QVariant &value)
{
    addAttribute(g_propertyAttrMap[attribute], value);
}

void TPropertyItem::addAttribute(const QString &name, const QVariant &value)
{
    if(mAttributes[name] == value)
        return;

    mAttributes[name] = value;

    emit attributeChanged(name, value);
}

void TPropertyItem::addAttribute(const PropertyAttribute &attribute, const QVariant &value)
{
    addAttribute(g_propertyAttrMap[attribute], value);
}

void TPropertyItem::setReadOnly(bool readOnly)
{
    addAttribute(g_propertyAttrMap[PA_READ_ONLY], readOnly);
}

QVariant TPropertyItem::value() const
{
    return mValue;
}

void TPropertyItem::setValue(const QVariant &value, bool emitSignal)
{
    if(mValue == value)
        return;

    QVariant oldValue = mValue;
    mValue = value;

    if(emitSignal)
        emit valueChanged(oldValue, value);
}

void TPropertyItem::setNewValue(const QVariant &value)
{
    if(mValue == value)
        return;

    if(mDocument)
    {
        TPropertyUndoCommand *undoCommand = new TPropertyUndoCommand(this, mPropertyId, value);
        mDocument->addUndoCommand(undoCommand);
    }
}

PropertyID TPropertyItem::propertyId() const
{
    return mPropertyId;
}

QList<TPropertyItem *> TPropertyItem::subPropertyItems() const
{
    return mSubPropertyItems;
}

void TPropertyItem::setSubPropertyItems(const QList<TPropertyItem *> &subPropertyItems)
{
    mSubPropertyItems = subPropertyItems;
}

void TPropertyItem::addSubPropertyItems(const QList<TPropertyItem *> &subPropertyItems)
{
    mSubPropertyItems += subPropertyItems;
}

void TPropertyItem::addSubPropertyItem(TPropertyItem *propertyItem)
{
    QList<TPropertyItem *> propertyItemList;
    propertyItemList.append(propertyItem);
    addSubPropertyItems(propertyItemList);
}

