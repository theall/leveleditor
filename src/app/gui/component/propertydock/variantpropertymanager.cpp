#include "variantpropertymanager.h"

#include <QFileInfo>

class TFilePathPropertyType {};
class TStringExPropertyType {};
class TPixmapPropertyType {};
class TSoundSetPropertyType {};
class TSoundItemPropertyType {};
class TSoundItemSourcePropertyType {};
Q_DECLARE_METATYPE(TPixmapPropertyType)
Q_DECLARE_METATYPE(TSoundSetPropertyType)
Q_DECLARE_METATYPE(TSoundItemPropertyType)
Q_DECLARE_METATYPE(TSoundItemSourcePropertyType)
Q_DECLARE_METATYPE(TFilePathPropertyType)
Q_DECLARE_METATYPE(TStringExPropertyType)

TVariantPropertyManager::TVariantPropertyManager(QObject *parent)
    : QtVariantPropertyManager(parent)
    , mSuggestionsAttribute(QStringLiteral("suggestions"))
    , mImageMissingIcon(QStringLiteral(":/other/images/image-missing.png"))
{
    mImageMissingIcon.addPixmap(QPixmap(QStringLiteral("://images/32x32/image-missing.png")));
}

QVariant TVariantPropertyManager::context(const QtProperty *property) const
{
    if (mValues.contains(property))
        return mValues[property].context;
    return QVariant();
}

QVariant TVariantPropertyManager::value(const QtProperty *property) const
{
    if (mValues.contains(property))
        return mValues[property].text;
    return QtVariantPropertyManager::value(property);
}

bool TVariantPropertyManager::isPropertyTypeSupported(int propertyType) const
{
    if(propertyType == stringExTypeId()
        || propertyType == pixmapTypeId()
        || propertyType == soundSetTypeId()
        || propertyType == soundItemTypeId()
        || propertyType == soundItemSourceTypeId())
        return true;

    return QtVariantPropertyManager::isPropertyTypeSupported(propertyType);
}

int TVariantPropertyManager::valueType(int propertyType) const
{
    if (propertyType == stringExTypeId()
        || propertyType == soundSetTypeId()
        || propertyType == soundItemTypeId()
        || propertyType == soundItemSourceTypeId())
        return QVariant::String;
    else if(propertyType == pixmapTypeId())
        return QVariant::Pixmap;

    return QtVariantPropertyManager::valueType(propertyType);
}

QStringList TVariantPropertyManager::attributes(int propertyType) const
{
    return QtVariantPropertyManager::attributes(propertyType);
}

int TVariantPropertyManager::attributeType(int propertyType,
                                          const QString &attribute) const
{
    return QtVariantPropertyManager::attributeType(propertyType, attribute);
}

QVariant TVariantPropertyManager::attributeValue(const QtProperty *property,
                                                const QString &attribute) const
{
    if(mValues.contains(property)) {
        if (attribute == QLatin1String("filter"))
            return mValues[property].context;
        return QVariant();
    }
    if (attribute == mSuggestionsAttribute && mSuggestions.contains(property))
        return mSuggestions[property];

    return QtVariantPropertyManager::attributeValue(property, attribute);
}

int TVariantPropertyManager::enumTypeId()
{
    return QtVariantPropertyManager::enumTypeId();
}

int TVariantPropertyManager::flagTypeId()
{
    return QtVariantPropertyManager::flagTypeId();
}

int TVariantPropertyManager::groupTypeId()
{
    return QtVariantPropertyManager::groupTypeId();
}

int TVariantPropertyManager::stringExTypeId()
{
    return qMetaTypeId<TStringExPropertyType>();
}

int TVariantPropertyManager::pixmapTypeId()
{
    return qMetaTypeId<TPixmapPropertyType>();
}

int TVariantPropertyManager::soundSetTypeId()
{
    return qMetaTypeId<TSoundSetPropertyType>();
}

int TVariantPropertyManager::soundItemTypeId()
{
    return qMetaTypeId<TSoundItemPropertyType>();
}

int TVariantPropertyManager::soundItemSourceTypeId()
{
    return qMetaTypeId<TSoundItemSourcePropertyType>();
}

QString TVariantPropertyManager::valueText(const QtProperty *property) const
{
    if (mValues.contains(property)) {
        return mValues[property].text.toString();
    }

    return QtVariantPropertyManager::valueText(property);
}

QIcon TVariantPropertyManager::valueIcon(const QtProperty *property) const
{
    if (mValues.contains(property)) {
        QVariant context = mValues[property].context;
        int typeId = propertyType(property);
        if(typeId == pixmapTypeId()) {
            QPixmap p = context.value<QPixmap>();
            if(p.isNull())
                return QIcon::fromTheme(QLatin1String("image-missing"), mImageMissingIcon);
            else
                return QIcon(p);
        }
    }

    return QtVariantPropertyManager::valueIcon(property);
}

void TVariantPropertyManager::setValue(QtProperty *property, const QVariant &val, const QVariant &context)
{
    if (mValues.contains(property)) {
        Data d = mValues[property];
        if (d.text==val && d.context==context)
            return;
        d.text = val;
        d.context = context;
        mValues[property] = d;
        emit propertyChanged(property);
        emit valueChanged(property, val);
    }
}

void TVariantPropertyManager::setValue(QtProperty *property, const QVariant &val)
{
    if (mValues.contains(property)) {
        Data d = mValues[property];
        if (d.text==val)
            return;
        d.text = val;
        mValues[property] = d;
        emit propertyChanged(property);
        emit valueChanged(property, val);
    }
    QtVariantPropertyManager::setValue(property, val);
}

void TVariantPropertyManager::setAttribute(QtProperty *property,
                                          const QString &attribute,
                                          const QVariant &val)
{
    if (mValues.contains(property)) {
        if (attribute == QLatin1String("filter")) {
            if (val.type() != QVariant::String && !val.canConvert(QVariant::String))
                return;
            QString str = val.toString();
            Data d = mValues[property];
            if (d.context == str)
                return;
            d.context = str;
            mValues[property] = d;
            emit attributeChanged(property, attribute, str);
        }
        return;
    }

    if (attribute == mSuggestionsAttribute && mSuggestions.contains(property))
        mSuggestions[property] = val.toStringList();

    QtVariantPropertyManager::setAttribute(property, attribute, val);
}

void TVariantPropertyManager::initializeProperty(QtProperty *property)
{
    const int type = propertyType(property);
    if (type == stringExTypeId())
        mValues[property] = Data();
    else if (type == pixmapTypeId())
        mValues[property] = Data();
    else if(type == soundSetTypeId())
        mValues[property] = Data();
    else if(type == soundItemTypeId())
        mValues[property] = Data();
    else if(type == soundItemSourceTypeId())
        mValues[property] = Data();
    else if (type == QVariant::String)
        mSuggestions[property] = QStringList();

    QtVariantPropertyManager::initializeProperty(property);
}

void TVariantPropertyManager::uninitializeProperty(QtProperty *property)
{
    mValues.remove(property);
    mSuggestions.remove(property);
    QtVariantPropertyManager::uninitializeProperty(property);
}
