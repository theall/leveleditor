#ifndef GENERIC_HPP
#define GENERIC_HPP

#define DECL_GENERIC_SLOTS(NAME) \
    void slot##NAME##Inserted(const T##NAME##List &objectList, const QList<int> &indexList);\
    void slot##NAME##Removed(const T##NAME##List &objectList, const QList<int> &indexList)

#define DECL_GENERIC_VARS(NAME) \
    T##NAME##ItemList m##NAME##ItemList;\
    QMap<T##NAME*, T##NAME##Item*> m##NAME##ItemMap;\
    T##NAME##Item *internalAdd(T##NAME *area)

#define CONNECT_GENERIC_SLOTS(model,NAME)\
connect(model, SIGNAL(objectInserted(T##NAME##List,QList<int>)), this, SLOT(slot##NAME##Inserted(T##NAME##List,QList<int>)));\
connect(model, SIGNAL(objectRemoved(T##NAME##List,QList<int>)), this, SLOT(slot##NAME##Removed(T##NAME##List,QList<int>)))

#define IMPL_GENERIC_SLOTS(NAME) \
void T##NAME##LayerItem::slot##NAME##Inserted(const T##NAME##List &objectList, const QList<int> &)\
{\
    for(T##NAME *object : objectList)\
        internalAdd(object);\
    calcBoundingRect();\
}\
void T##NAME##LayerItem::slot##NAME##Removed(const T##NAME##List &objectList, const QList<int> &)\
{\
    for(T##NAME *object : objectList) {\
        T##NAME##Item *objectItem = m##NAME##ItemMap[object];\
        if(objectItem) {\
            delete objectItem;\
            m##NAME##ItemList.removeAll(objectItem);\
        }\
        m##NAME##ItemMap.remove(object);\
    }\
    calcBoundingRect();\
}\
T##NAME##Item *T##NAME##LayerItem::internalAdd(T##NAME *object)\
{\
    T##NAME##Item *objectItem = new T##NAME##Item(object, this);\
    m##NAME##ItemList.append(objectItem);\
    m##NAME##ItemMap.insert(object, objectItem);\
    return objectItem;\
}

#endif // GENERIC_HPP
