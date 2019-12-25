#ifndef TGENERICMODEL_H
#define TGENERICMODEL_H

#include <QList>
#include "basemodel.h"

class TBaseModel;
template<class T>
class TGenericModel : public TBaseModel
{
public:
    TGenericModel(Type type, QObject *parent = Q_NULLPTR) :
        TBaseModel(type, parent)
    {

    };

    T *getObject(int index) const {
        if(index<0 || index>= mObjectList.size())
            return nullptr;

        return mObjectList.at(index);
    }

    virtual void insertObjects(const QList<T*> &objectList, const QList<int> &indexList) {
        insertObject(objectList, indexList);
    };

    virtual QList<int> removeObjects(const QList<T*> &objectList) {
        return removeObject(objectList);
    };

    virtual QList<int> moveObjects(const QList<T*> &, const QList<int> &) {
        return QList<int>();
    };

    int currentIndex(TObject *object)
    {
        T *Object = dynamic_cast<T*>(object);
        return mObjectList.indexOf(Object);
    }

    QList<int> removeFromContainer(QList<T*> &container, QList<T*> &objectList)
    {
        QList<int> indexRemoved;
        for(T *object : objectList) {
            int index = container.indexOf(object);
            container.removeAt(index);
            indexRemoved.append(index);
        }
        return indexRemoved;
    }

    QList<T> removeFromContainer(QList<T*> &container, QList<int> &indexList)
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

protected:
    QList<T*> mObjectList;

    QList<T*> convert(const TObjectList &objectList)
    {
        QList<T*> list;
        for(TObject *object : objectList) {
            list.append((T*)object);
        }
        return list;
    }

    TObjectList convert(const QList<T*> &objectList) {
        TObjectList list;
        for(T *object : objectList) {
            list.append((TObject*)object);
        }
        return list;
    }

    void insertObject(T *object, int index)
    {
        if(!object)
            return;

        QList<int> indexList;
        mObjectList.append(object);
        indexList.append(index);
        insertObject(mObjectList, indexList);
    }
    void insertObject(const QList<T*> &objectList, const QList<int> &indexList)
    {
        QList<T*> objectInsertedList = objectList;
        QList<int> insertedIndexList = indexList;
        internalInsert(objectInsertedList, insertedIndexList);
        onObjectInserted(convert(objectList), insertedIndexList);
    }

private:
    void internalInsert(const QList<T*> &objectList, QList<int> &indexList)
    {
        QList<T*> objectInsertedList;
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
            T *object = objectList.at(i);
            if(!object)
                continue;

            int objectCount = mObjectList.size();
            int index = indexList.at(i);
            if(index<0 || index>=objectCount) {
                index = objectCount;
                mObjectList.append(object);
            } else {
                mObjectList.insert(index, object);
            }
            objectInsertedList.append(object);
            insertedIndexList.append(index);
        }
        indexList = insertedIndexList;
    }

    int removeObject(int index)
    {
        QList<int> indexList;
        indexList.append(index);

        QList<int> indexRemovedList = removeObject(indexList);
        index = -1;
        if(!indexRemovedList.isEmpty())
            index = indexRemovedList.at(0);
        return index;
    }

    int removeObject(T *object)
    {
        QList<T*> objectList;
        objectList.append(object);
        QList<int> indexRemovedList = removeObject(objectList);
        int index = -1;
        if(!indexRemovedList.isEmpty())
            index = indexRemovedList.at(0);
        return index;
    }

    QList<int> removeObject(const QList<int> &indexList)
    {
        QList<T*> objectList;
        QList<int> indexRemoved = indexList;
        objectList = removeFromContainer(mObjectList, indexRemoved);
        if(!indexRemoved.isEmpty()) {
            onObjectRemoved(convert(objectList), indexRemoved);
        }
        return indexRemoved;
    }

    QList<int> removeObject(const QList<T*> &objectList)
    {
        QList<int> indexRemoved;
        QList<T*> objectListRemoved = objectList;
        indexRemoved = removeFromContainer(mObjectList, objectListRemoved);
        if(!indexRemoved.isEmpty()) {
            onObjectRemoved(convert(objectList), indexRemoved);
        }
        return indexRemoved;
    }

    // TIO interface
public:
    void saveToStream(QDataStream &) const {

    }

    void readFromStream(QDataStream &) {

    }

    // TBaseModel interface
public:
    void insertObjects(const TObjectList &objectList, const QList<int> &indexList) {
        insertObjects(convert(objectList), indexList);
    }

    QList<int> removeObjects(const TObjectList &objectList) {
        return removeObjects(convert(objectList));
    }
};

#endif // TGENERICMODEL_H
