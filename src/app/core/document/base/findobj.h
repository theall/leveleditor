#ifndef FINDOBJ_H
#define FINDOBJ_H

#define FIND_OBJECT \
    QObject *obj = parent;\
    while (obj) {\
        mDocument = qobject_cast<TDocument*>(obj);\
        if(mDocument)\
            break;\
        obj = obj->parent();\
    }\
    if(!mDocument)\
        throw QString("File:%1, Line:%2: Parent must be document.").arg(__FILE__).arg(__LINE__)

#endif // FINDOBJ_H
