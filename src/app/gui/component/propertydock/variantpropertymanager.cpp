#include "variantpropertymanager.h"
#include "propertymanager/dirpropertymanager.h"

#include <QFileInfo>

#define DECL_NEW_METATYPE(NAME) \
class T##NAME##PropertyType {};\
Q_DECLARE_METATYPE(T##NAME##PropertyType)

#define GET_METATYPE(NAME) \
qMetaTypeId<T##NAME##PropertyType>()

DECL_NEW_METATYPE(StringEx)
DECL_NEW_METATYPE(Pixmap)
DECL_NEW_METATYPE(SoundSet)
DECL_NEW_METATYPE(SoundItem)
DECL_NEW_METATYPE(SoundItemSource)
DECL_NEW_METATYPE(Dir)

struct CustomType {
    int type;
    QVariant::Type valueType;
};

static const CustomType g_custom_type_list[] = {
    {GET_METATYPE(StringEx), QVariant::String},
    {GET_METATYPE(Pixmap), QVariant::Pixmap},
    {GET_METATYPE(SoundSet), QVariant::String},
    {GET_METATYPE(SoundItem), QVariant::String},
    {GET_METATYPE(SoundItemSource), QVariant::String},
    {GET_METATYPE(Dir), QVariant::Int},
    {0, QVariant::Invalid}
};
typedef QMap<int, int> CustomTypeMap;
Q_GLOBAL_STATIC(CustomTypeMap, customTypeMap)

TVariantPropertyManager::TVariantPropertyManager(QObject *parent) :
    QtVariantPropertyManager(parent)
{
    TDirPropertyManager *dirPropertyManager = new TDirPropertyManager(this);
    registerManager(GET_METATYPE(Dir), dirPropertyManager);

    connect(dirPropertyManager, SIGNAL(valueChanged(QtProperty *, int)),
                this, SLOT(slotValueChanged(QtProperty *, int)));

    for(int i=0;;i++) {
        CustomType customType = g_custom_type_list[i];
        if(customType.valueType == QVariant::Invalid)
            break;
        customTypeMap()->insert(customType.type, customType.valueType);
    }
}

QVariant TVariantPropertyManager::value(const QtProperty *property) const
{
    QtAbstractPropertyManager *manager = property->propertyManager();
    if(TDirPropertyManager *dirManager = qobject_cast<TDirPropertyManager *>(manager))
        return dirManager->value(property);

    return QtVariantPropertyManager::value(property);
}

bool TVariantPropertyManager::isPropertyTypeSupported(int propertyType) const
{
    if(customTypeMap()->contains(propertyType))
        return true;

    return QtVariantPropertyManager::isPropertyTypeSupported(propertyType);
}

int TVariantPropertyManager::valueType(int propertyType) const
{
    if(customTypeMap()->contains(propertyType))
        return customTypeMap()->value(propertyType);

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
    return QtVariantPropertyManager::attributeValue(property, attribute);
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

int TVariantPropertyManager::dirTypeId()
{
    return qMetaTypeId<TDirPropertyType>();
}

QString TVariantPropertyManager::valueText(const QtProperty *property) const
{
    return QtVariantPropertyManager::valueText(property);
}

QIcon TVariantPropertyManager::valueIcon(const QtProperty *property) const
{
    return QtVariantPropertyManager::valueIcon(property);
}

void TVariantPropertyManager::setValue(QtProperty *property, const QVariant &val)
{
    if(isCustomizedProperty(property)) {
        QtProperty *internProp = getInternalProperty(property);
        if(!internProp)
            return;

        if (TDirPropertyManager *dirManager = qobject_cast<TDirPropertyManager *>(internProp->propertyManager())) {
            dirManager->setValue(internProp, val.value<int>());
        }
    } else {
        QtVariantPropertyManager::setValue(property, val);
    }
}

void TVariantPropertyManager::setAttribute(QtProperty *property,
                                          const QString &attribute,
                                          const QVariant &val)
{
    QtVariantPropertyManager::setAttribute(property, attribute, val);
}

void TVariantPropertyManager::initializeProperty(QtProperty *property)
{
    QtVariantPropertyManager::initializeProperty(property);
}

void TVariantPropertyManager::uninitializeProperty(QtProperty *property)
{
    QtVariantPropertyManager::uninitializeProperty(property);
}

bool TVariantPropertyManager::isCustomizedPropertyType(int propertyType) const
{
    return customTypeMap()->contains(propertyType);
}

bool TVariantPropertyManager::isCustomizedProperty(const QtProperty *property) const
{
    return isCustomizedPropertyType(propertyType(property));
}

void TVariantPropertyManager::slotValueChanged(QtProperty *property, int value)
{
    emit valueChanged(internalToProperty(property), QVariant(value));
}
