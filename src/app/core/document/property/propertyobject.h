#ifndef PROPERTYOBJECT_H
#define PROPERTYOBJECT_H

#include "propertysheet.h"

class TPropertyObject : public QObject
{
    Q_OBJECT

public:
    TPropertyObject(QObject *parent = nullptr);
    ~TPropertyObject();

    TPropertySheet *propertySheet() const;
    TPropertyItems propertyItems() const;

    QVariant getValue(const QString &name) const;
    void setValue(const QString &name, const QVariant &value);
    TPropertyItem *operator [](const QString &name) const;
    TPropertyItem *get(const QString &name) const;
    QVariant getValue(const PropertyID &pid) const;
    void setValue(const PropertyID &pid, const QVariant &value);
    TPropertyItem *operator [](const PropertyID &pid) const;
    TPropertyItem *get(const PropertyID &pid) const;

    QString toString() const;

protected:
    TPropertySheet *mPropertySheet;
};

#endif // PROPERTYOBJECT_H
