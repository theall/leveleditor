#include "respawnmodel.h"

TRespawnModel::TRespawnModel(QObject *parent) :
    TGenericModel<TRespawn>(TBaseModel::RESPAWN, parent)
{
    setName(tr("Respawn"));
    setIcon(QIcon(":/scenemodel/images/respawn.png"));
}

void TRespawnModel::clear()
{
    mObjectList.clear();
}

TPointObject *TRespawnModel::getTPointObject(int index)
{
    if(index == -1)
        return nullptr;
    TRespawn *respawn= mObjectList.at(index/2);
    if(index%2)
        return respawn->respownPointObject();
    return respawn->startPointObject();
}

void TRespawnModel::readFromStream(QDataStream &stream)
{
    int respawnPointAmount = 0;
    stream >> respawnPointAmount;
    if(respawnPointAmount > 0xffff)
        throw tr("Invalid map format!");

    mObjectList.clear();
    for(int i=0;i<respawnPointAmount;i++) {
        TRespawn *respawn = new TRespawn(this);
        respawn->readFromStream(stream);
        mObjectList.append(respawn);
    }
}

void TRespawnModel::saveToStream(QDataStream &stream) const
{
    int respawnSize = mObjectList.size();
    stream << respawnSize;

    for(int i=0;i<respawnSize;i++) {
        TRespawn *respawn = mObjectList.at(i);
        respawn->saveToStream(stream);
    }
}

//QModelIndex TRespawnModel::index(int row, int column, const QModelIndex &parent) const
//{
//    if(!hasIndex(row, column, parent))
//        return QModelIndex();

//    QObject *data = (QObject*)parent.internalPointer();
//    if (!parent.isValid()) {
//        TRespawn *respawn = mObjectList.at(row);
//        if(respawn)
//            return createIndex(row, column, respawn);
//    } else if(TRespawn *respawn = dynamic_cast<TRespawn*>(data)) {
//        TPointObject *pointOjbect;
//        if(row == 0) {
//            pointOjbect = respawn->respownPointObject();
//        }else
//            pointOjbect = respawn->startPointObject();
//        if(pointOjbect)
//            return createIndex(row, column, pointOjbect);
//    }
//    return QModelIndex();

//    return QModelIndex(row, column, parent);
//}

//QModelIndex TRespawnModel::parent(const QModelIndex &index) const
//{
//    if (!index.isValid())
//        return QModelIndex();

//    QObject *data = (QObject*)index.internalPointer();
//    if(TPointObject *pointOjbect = dynamic_cast<TPointObject*>(data)) {
//        if(TRespawn *respawn = dynamic_cast<TRespawn*>(pointOjbect->parent())) {
//            return createIndex(0, 0, respawn);
//        }
//    }
//    return QModelIndex();
//}

int TRespawnModel::rowCount(const QModelIndex &) const
{
//    if(!parent.isValid()) {
//        return mObjectList.size();
//    } else {
//        return 2;
//    }
    return mObjectList.size()*2;
}

int TRespawnModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant TRespawnModel::data(const QModelIndex &index, int role) const
{
//    QObject* data = (QObject*)index.internalPointer();
//    if(TRespawn *respawn = dynamic_cast<TRespawn*>(data)) {
//        if(role==Qt::DisplayRole) {
//            return tr("respawn %1").arg(mObjectList.indexOf(respawn)+1);
//        }
//    } else if(TPointObject *pointObject = dynamic_cast<TPointObject*>(data)) {
//        if(role==Qt::DisplayRole) {
//            return pointObject->typeString();
//        }
//    }
    int row = index.row();
    if(row>=0 && row<(mObjectList.size()*2))
    {
        if(role==Qt::DisplayRole)
        {
            int count = row/2;
            if(row%2)
                return tr("RespownPoint %1").arg(count+1);
            return tr("StartPoint %1").arg(count+1);
        }
    }
    return QVariant();
}

TRespawnList TRespawnModel::respawnList() const
{
    return mObjectList;
}

int TRespawnModel::indexOf(TRespawn *respawn) const
{
    return mObjectList.indexOf(respawn);
}

int TRespawnModel::pointObjectIndex(TPointObject *pointObject)
{
    int index = 0;
    for(TRespawn *respawn: mObjectList){
        if(respawn->startPointObject() == pointObject)
            return index*2;
        if(respawn->respownPointObject() == pointObject)
            return index*2+1;
        index++;
    }
    return index;
}

void TRespawnModel::onObjectInserted(const TObjectList &objectList, const QList<int> &indexList)
{
    emit objectInserted(convert(objectList), indexList);
}

void TRespawnModel::onObjectRemoved(const TObjectList &objectList, const QList<int> &indexList)
{
    emit objectRemoved(convert(objectList), indexList);
}

void TRespawnModel::onObjectMove(const TObjectList &objectList, const QList<int> &posList)
{

}
