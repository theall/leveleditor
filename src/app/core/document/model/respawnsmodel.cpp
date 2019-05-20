#include "respawnsmodel.h"

TRespawnsModel::TRespawnsModel(QObject *parent) :
    TBaseModel(TBaseModel::RESPAWN, parent)
{
    setName(tr("Respawn"));
}

void TRespawnsModel::clear()
{
    mRespawnPointList.clear();
}

void TRespawnsModel::readFromStream(QDataStream &stream)
{
    int respawnPointAmount = 0;
    stream >> respawnPointAmount;
    if(respawnPointAmount > 0xffff)
        throw tr("Invalid map format!");
    mRespawnPointList.clear();
    for(int i=0;i<respawnPointAmount;i++) {
        QPoint respawnPoint;
        stream >> respawnPoint;
        mRespawnPointList.append(respawnPoint);
    }
}

void TRespawnsModel::saveToStream(QDataStream &stream) const
{

}

int TRespawnsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mRespawnPointList.size();
}

int TRespawnsModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant TRespawnsModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row>=0 && row<mRespawnPointList.size())
    {
        if(role==Qt::DisplayRole)
        {
            return tr("Respawn Point %d").arg(row+1);
        }
    }
    return QVariant();
}

QList<QPoint> TRespawnsModel::respawnPointList() const
{
    return mRespawnPointList;
}
