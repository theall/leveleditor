#include "respawnmodel.h"

TRespawnModel::TRespawnModel(QObject *parent) :
    TGenericModel<TRespawn>(TBaseModel::ANIMATION, parent)
{
    setName(tr("Respawn"));
}

void TRespawnModel::clear()
{
    mObjectList.clear();
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

int TRespawnModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mObjectList.size();
}

int TRespawnModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant TRespawnModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row>=0 && row<mObjectList.size())
    {
        if(role==Qt::DisplayRole)
        {
            return tr("Respawn Point %1").arg(row+1);
        }
    }
    return QVariant();
}

TRespawnList TRespawnModel::respawnList() const
{
    return mObjectList;
}

void TRespawnModel::onObjectInserted(const TObjectList &, const QList<int> &indexList)
{
    emit objectInserted(mObjectList, indexList);
}

void TRespawnModel::onObjectRemoved(const TObjectList &, const QList<int> &indexList)
{
    emit objectRemoved(mObjectList, indexList);
}
