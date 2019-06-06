#include "respawnmodel.h"

TRespawnModel::TRespawnModel(QObject *parent) :
    TBaseModel(TBaseModel::RESPAWN, parent)
{
    setName(tr("Respawn"));
}

void TRespawnModel::clear()
{
    mRespawnList.clear();
}

void TRespawnModel::readFromStream(QDataStream &stream)
{
    int respawnPointAmount = 0;
    stream >> respawnPointAmount;
    if(respawnPointAmount > 0xffff)
        throw tr("Invalid map format!");

    mRespawnList.clear();
    for(int i=0;i<respawnPointAmount;i++) {
        TRespawn *respawn = new TRespawn(this);
        respawn->readFromStream(stream);
        mRespawnList.append(respawn);
    }
}

void TRespawnModel::saveToStream(QDataStream &stream) const
{
    int respawnSize = mRespawnList.size();
    stream << respawnSize;

    for(int i=0;i<respawnSize;i++) {
        stream << mRespawnList.at(i);
    }
}

int TRespawnModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mRespawnList.size();
}

int TRespawnModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant TRespawnModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row>=0 && row<mRespawnList.size())
    {
        if(role==Qt::DisplayRole)
        {
            return tr("Respawn Point %d").arg(row+1);
        }
    }
    return QVariant();
}

TRespawnList TRespawnModel::respawnList() const
{
    return mRespawnList;
}

IMPL_GENERIC_FUNCTIONS(Respawn)
