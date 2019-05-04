#include "platformsmodel.h"

TPlatformsModel::TPlatformsModel(QObject *parent) :
    TBaseModel(parent)
{
    setName(tr("Platform"));
}

void TPlatformsModel::readFromStream(QDataStream &stream)
{
    int platAmount;
    stream >> platAmount;
    mPlatList.clear();
    for(int i=0;i<platAmount;i++) {
        TPlat *plat = new TPlat(this);
        plat->readFromStream(stream);
        mPlatList.append(plat);
    }
}

void TPlatformsModel::saveToStream(QDataStream &stream) const
{

}

int TPlatformsModel::rowCount(const QModelIndex &parent) const
{
    return mPlatList.size();
}

int TPlatformsModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant TPlatformsModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row>=0 && row<mPlatList.size())
    {
        if(role==Qt::DisplayRole)
        {
            return tr("Platform %d").arg(row+1);
        }
    }
    return QVariant();
}

TPlatList TPlatformsModel::platList() const
{
    return mPlatList;
}

void TPlatformsModel::clear()
{
    mPlatList.clear();
}
