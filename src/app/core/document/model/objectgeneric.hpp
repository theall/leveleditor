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

#endif // GENERIC_H
