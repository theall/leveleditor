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

protected:
    TPropertySheet *mPropertySheet;
};

#endif // PROPERTYOBJECT_H
