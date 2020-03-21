#include "clipboard.h"

#include <QMap>

#define ADD_OBJECT(T, objectList) \
    for(QByteArray byteArray : mDataList) \
    { \
        T *t = new T(); \
        QDataStream stream(&byteArray, QIODevice::ReadWrite); \
        t->readFromStream(stream); \
        objectList.append(t); \
    }

IMPL_SINGLE_INSTANCE(TClipboard)
TClipboard::TClipboard(QObject *parent) :
    QObject(parent)
{

}

TClipboard::~TClipboard()
{
    
}

TObject::Type TClipboard::getType() const
{
    return mType;
}

void TClipboard::setData(const TObjectItemList &objectItemList, TBaseModel *baseModel)
{
    mPointList.clear();
    mType = TObject::INVALID;
    mDataList.clear();

    if(objectItemList.isEmpty())
        return;

    TObjectList objectList;
    QList<QPointF> pointList;
    TObjectItem *firstItem = objectItemList.at(0);
    QRectF rect = firstItem->getBoundingRect();
    mType = firstItem->objectType();

    for(TObjectItem *objectItem: objectItemList)
    {
        rect = rect.united(objectItem->getBoundingRect());
        pointList.append(objectItem->getCurrentPos());
        objectList.append(objectItem->object());
    }

    QPointF centerPos = rect.center();
    for(QPointF pos : pointList)
        mPointList.append(centerPos-pos);

    setIndexList(objectList, baseModel);
    QMap<int, QByteArray> map;
    int i=0;
    for(TObject *object : objectList) {
        QByteArray byteArray;
        QDataStream stream(&byteArray, QIODevice::WriteOnly);
        object->saveToStream(stream);
        map.insert(mIndexList.at(i), byteArray);
        i++;
    }
    mDataList = map.values();
}

bool TClipboard::whetherObject(const TObject::Type &type) const
{
    if(mType != type)
        return false;
    return true;
}

bool TClipboard::isEmpty()
{
    return mDataList.isEmpty();
}

QList<QPointF> TClipboard::getPointList() const
{
    return mPointList;
}

TObjectList TClipboard::getObjectList() const
{   
    TObjectList objectList;
    switch (mType) {
    case TObject::ANIMATION :
        ADD_OBJECT(TAnimation, objectList);
        break;
    case TObject::AREA :
        ADD_OBJECT(TArea, objectList);
        break;
    case TObject::BOX :
        ADD_OBJECT(TBox, objectList);
        break;
    case TObject::DAREA :
        ADD_OBJECT(TDArea, objectList);
        break;
    case TObject::ENEMY :
        ADD_OBJECT(TEnemy, objectList);
        break;
    case TObject::FRAME :
        ADD_OBJECT(TFrame, objectList);
        break;
    case TObject::TRIGGER :
        ADD_OBJECT(TTrigger, objectList);
        break;
    case TObject::PLAT :
        ADD_OBJECT(TPlat, objectList);
        break;
    case TObject::TILE :
        ADD_OBJECT(TTile, objectList);
        break;
     default :
        break;
    }
    return objectList;
}

void TClipboard::setIndexList(const TObjectList &objectList, TBaseModel *baseModel)
{
    if(TAreaModel *areaModel = dynamic_cast<TAreaModel*>(baseModel)) {
        for(TObject *object : objectList)
            mIndexList.append(areaModel->areaList().indexOf(dynamic_cast<TArea*>(object)));
    } else if(TBoxModel *boxModel = dynamic_cast<TBoxModel*>(baseModel)) {
        for(TObject *object : objectList)
            mIndexList.append(boxModel->boxList().indexOf(dynamic_cast<TBox*>(object)));
    } else if(TDAreaModel *dareaModel = dynamic_cast<TDAreaModel*>(baseModel)) {
        for(TObject *object : objectList)
            mIndexList.append(dareaModel->dAreaList().indexOf(dynamic_cast<TDArea*>(object)));
    } else if(TEnemyFactoryModel *enemyFactoryModel = dynamic_cast<TEnemyFactoryModel*>(baseModel)) {
        for(TObject *object : objectList) {
            if(TEnemyFactory *enemyFactory = dynamic_cast<TEnemyFactory*>(object)){
                mIndexList.append(enemyFactoryModel->enemyFactoryList().indexOf(enemyFactory));
            } else {
                TEnemyModel *enemyModel = dynamic_cast<TEnemyModel*>(baseModel);
                TEnemyFactory *enemyFactory1 = enemyModel->enemyFactory();
                mIndexList.append(enemyFactory1->enemyList().indexOf(dynamic_cast<TEnemy*>(object)));
            }
        }
    } else if(TTriggerModel *triggerModel = dynamic_cast<TTriggerModel*>(baseModel)) {
        for(TObject *object : objectList)
            mIndexList.append(triggerModel->triggerList().indexOf(dynamic_cast<TTrigger*>(object)));
    } else if(TPlatModel *platModel = dynamic_cast<TPlatModel*>(baseModel)) {
        for(TObject *object : objectList)
            mIndexList.append(platModel->platList().indexOf(dynamic_cast<TPlat*>(object)));
    } else if(TTileModel *tileModel = dynamic_cast<TTileModel*>(baseModel)) {
        for(TObject *object : objectList)
            mIndexList.append(tileModel->tileList().indexOf(dynamic_cast<TTile*>(object)));
    }
}
