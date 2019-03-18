#ifndef TOBJECT_H
#define TOBJECT_H

#include "../../base/propertyobject.h"

class TObject : public TPropertyObject
{
public:
    enum Type {
        AREA,
        DAREA,
        BOX,
        PLAT,
        TILE,
        WALL
    };

    TObject(Type type, QObject *parent = nullptr);

    Type type() const;

private:
    Type mType;
};

#endif // TOBJECT_H
