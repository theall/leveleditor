#include "dirpropertymanager.h"

#include <QIcon>

int valueToIndex(int value) {
    if(value == 2)
        return 0;
    else if(value == 4)
        return 1;
    return 2;
}

int indexToValue(int value) {
    if(value == 0)
        return 2;
    else if(value == 1)
        return 4;
    return 0;
}

class TDirPropertyManagerPrivate
{
    TDirPropertyManager *q_ptr;
    Q_DECLARE_PUBLIC(TDirPropertyManager)

public:
    TDirPropertyManagerPrivate()
    {

    }
    typedef QMap<const QtProperty *, int> PropertyValueMap;
    PropertyValueMap m_values;
};

/*!
    Creates a manager with the given \a parent.
*/
TDirPropertyManager::TDirPropertyManager(QObject *parent)
    : QtAbstractPropertyManager(parent)
{
    d_ptr = new TDirPropertyManagerPrivate;
    d_ptr->q_ptr = this;
}

/*!
    Destroys this manager, and all the properties it has created.
*/
TDirPropertyManager::~TDirPropertyManager()
{
    clear();
    delete d_ptr;
}

/*!
    Returns the given \a property's value.

    If the given \a property is not managed by this manager, this
    function returns a default int object.

    \sa setValue()
*/
int TDirPropertyManager::value(const QtProperty *property) const
{
    return d_ptr->m_values.value(property, 0);
}

int TDirPropertyManager::valueIndex(const QtProperty *property) const
{
    return valueToIndex(d_ptr->m_values.value(property, 0));
}

void TDirPropertyManager::setIndexValue(QtProperty *property, int val)
{
    setValue(property, indexToValue(val));
}

QStringList TDirPropertyManager::getEnumNames() const
{
    QStringList list;
    list.append(valueString(2));
    list.append(valueString(4));
    list.append(valueString(0));
    return list;
}

/*!
    \reimp
*/
QString TDirPropertyManager::valueText(const QtProperty *property) const
{
    const TDirPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return valueString(0);

    return valueString(it.value());
}

/*!
    \reimp
*/
QIcon TDirPropertyManager::valueIcon(const QtProperty *property) const
{
    const TDirPropertyManagerPrivate::PropertyValueMap::const_iterator it = d_ptr->m_values.constFind(property);
    if (it == d_ptr->m_values.constEnd())
        return QIcon();

    return QIcon();
}

/*!
    \fn void TDirPropertyManager::setValue(QtProperty *property, int value)

    Sets the value of the given \a property to \a value.

    \sa value(), valueChanged()
*/
void TDirPropertyManager::setValue(QtProperty *property, int value)
{
    const TDirPropertyManagerPrivate::PropertyValueMap::iterator it = d_ptr->m_values.find(property);
    if (it == d_ptr->m_values.end())
        return;

    if (it.value() == value)
        return;

    it.value() = value;

    emit propertyChanged(property);
    emit valueChanged(property, value);
}

/*!
    \reimp
*/
void TDirPropertyManager::initializeProperty(QtProperty *property)
{
    d_ptr->m_values[property] = 0;
}

/*!
    \reimp
*/
void TDirPropertyManager::uninitializeProperty(QtProperty *property)
{
    d_ptr->m_values.remove(property);
}

QString TDirPropertyManager::valueString(int value) const
{
    if(value == 2)
        return tr("Left");
    else if(value == 4)
        return tr("Right");
    return tr("Invalid");
}
