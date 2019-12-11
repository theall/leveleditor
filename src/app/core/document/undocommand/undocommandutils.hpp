#ifndef UNDOCOMMANDUTILS_H
#define UNDOCOMMANDUTILS_H

#include <QString>

#include "../../document/model/entity/object.h"

template<typename T>
QString getContextString(const QList<T> &objectList) {
    QString context = "";
    TObject::Type lastObjectType = TObject::INVALID;
    for(T _o : objectList) {
        TObject *object = dynamic_cast<TObject*>(_o);
        if(object && object->type() != lastObjectType)
        {
            lastObjectType = object->type();
            context += object->typeString() + " ";
            if(context.length() > 10)
                context += "...";
        }
    }
    return context;
}

#endif // UNDOCOMMANDUTILS_H
