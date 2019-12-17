#ifndef GENERIC_H
#define GENERIC_H

#include "entity/object.h"

template<typename T>
QList<T> convert(const TObjectList &objectList)
{
    QList<T> list;
    for(TObject *object : objectList) {
        list.append((T)object);
    }
    return list;
}

template<typename T>
TObjectList convert(const QList<T> &objectList)
{
    TObjectList list;
    for(T object : objectList) {
        list.append(object);
    }
    return list;
}

template<typename T>
void insertIntoContainer(QList<T> &container, QList<T> &objectList, QList<int> &indexList)
{
    QList<T> objectInsertedList;
    QList<int> insertedIndexList;
    int objectListSize = objectList.size();
    if(objectListSize != indexList.size()) {
        indexList.clear();
    }
    if(indexList.isEmpty()) {
        for(int i=0;i<objectListSize;i++) {
            indexList.append(-1);
        }
    }
    for(int i=0;i<objectListSize;i++) {
        T object = objectList.at(i);
        if(!object)
            continue;

        int objectCount = container.size();
        int index = indexList.at(i);
        if(index<0 || index>=objectCount) {
            index = objectCount;
            container.append(object);
        } else {
            container.insert(index, object);
        }
        objectInsertedList.append(object);
        insertedIndexList.append(index);
    }
    objectList = objectInsertedList;
    indexList = insertedIndexList;
}

template<typename T>
QList<int> removeFromContainer(QList<T> &container, QList<T> &objectList)
{
    QList<int> indexRemoved;
    for(T object : objectList) {
        int index = container.indexOf(object);
        container.removeAt(index);
        indexRemoved.append(index);
    }
    return indexRemoved;
}

template<typename T>
QList<T> removeFromContainer(QList<T> &container, QList<int> &indexList)
{
    QList<T> objectList;
    QList<int> indexRemoved;
    for(int i=0;i<indexList.size();i++) {
        int index = indexList.at(i);
        T object = container.at(index);
        container.removeAt(index);
        objectList.append(object);
        indexRemoved.append(index);
    }
    indexList = indexRemoved;
    return objectList;
}

#define DECL_GENERIC_FUNCTIONS(Type)\
    void insertObjects(const TObjectList &objectList, const QList<int> &indexList);\
    QList<int> removeObjects(const TObjectList &objectList);\
    void insert##Type(T##Type *object, int index = -1);\
    void insert##Type(const T##Type##List &objectList, const QList<int> &indexList = QList<int>());\
    int remove##Type(int index);\
    int remove##Type(T##Type *object);\
    QList<int> remove##Type(const QList<int> &indexList);\
    QList<int> remove##Type(const T##Type##List &objectList)

#define DECL_GENERIC_SIGNALS(Type)\
    void objectInserted(const T##Type##List &objectList, const QList<int> &indexList);\
    void objectRemoved(const T##Type##List &objectList, const QList<int> &indexList)

#define IMPL_GENERIC_FUNCTIONS(Type)\
void T##Type##Model::insert##Type(T##Type *object, int index)\
{\
    if(!object)\
        return;\
\
    T##Type##List objectList;\
    QList<int> indexList;\
    objectList.append(object);\
    indexList.append(index);\
    insert##Type(objectList, indexList);\
}\
\
void T##Type##Model::insert##Type(const T##Type##List &objectList, const QList<int> &indexList)\
{\
    T##Type##List objectInsertedList = objectList;\
    QList<int> insertedIndexList = indexList;\
    insertIntoContainer<T##Type*>(m##Type##List, objectInsertedList, insertedIndexList);\
    emit objectInserted(objectInsertedList, insertedIndexList);\
}\
\
int T##Type##Model::remove##Type(int index)\
{\
    QList<int> indexList;\
    indexList.append(index);\
\
    QList<int> indexRemovedList = remove##Type(indexList);\
    index = -1;\
    if(!indexRemovedList.isEmpty())\
        index = indexRemovedList.at(0);\
    return index;\
}\
\
int T##Type##Model::remove##Type(T##Type *object)\
{\
    T##Type##List objectList;\
    objectList.append(object);\
\
    QList<int> indexRemovedList = remove##Type(objectList);\
    int index = -1;\
    if(!indexRemovedList.isEmpty())\
        index = indexRemovedList.at(0);\
    return index;\
}\
\
QList<int> T##Type##Model::remove##Type(const QList<int> &indexList)\
{\
    T##Type##List objectList;\
    QList<int> indexRemoved = indexList;\
    objectList = removeFromContainer<T##Type*>(m##Type##List, indexRemoved);\
    if(!indexRemoved.isEmpty()) {\
        emit objectRemoved(objectList, indexRemoved);\
    }\
    return indexRemoved;\
}\
\
QList<int> T##Type##Model::remove##Type(const T##Type##List &objectList)\
{\
    QList<int> indexRemoved;\
    T##Type##List objectListRemoved = objectList;\
    indexRemoved = removeFromContainer<T##Type*>(m##Type##List, objectListRemoved);\
    if(!indexRemoved.isEmpty()) {\
        emit objectRemoved(objectList, indexRemoved);\
    }\
    return indexRemoved;\
}
#endif // GENERIC_H
