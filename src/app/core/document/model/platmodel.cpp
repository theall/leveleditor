#include "platmodel.h"
#include "basemodel.h"

TPlatModel::TPlatModel(QObject *parent) :
    TBaseModel(TBaseModel::PLAT, parent)
{
    setName(tr("Platform"));
}

void TPlatModel::readFromStream(QDataStream &stream)
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

void TPlatModel::saveToStream(QDataStream &stream) const
{
    stream << mPlatList.size();

    for(TPlat *plat : mPlatList) {
        plat->saveToStream(stream);
    }
}

int TPlatModel::rowCount(const QModelIndex &) const
{
    return mPlatList.size();
}

int TPlatModel::columnCount(const QModelIndex &) const
{
    return 1;
}

QVariant TPlatModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row>=0 && row<mPlatList.size())
    {
        if(role==Qt::DisplayRole)
        {
            return tr("Platform %1").arg(row+1);
        }
    }
    return QVariant();
}

TPlatList TPlatModel::platList() const
{
    return mPlatList;
}

QStringList TPlatModel::getPlatNames() const
{
    QStringList platNames;
    int i = 1;
    for(TPlat *plat : mPlatList) {
        if(!plat)
            continue;

        platNames.append(tr("Plat%1").arg(i++));
    }
    return platNames;
}

void TPlatModel::clear()
{
    mPlatList.clear();
}

TPlat *TPlatModel::createPlat()
{
    return new TPlat(this);
}

IMPL_GENERIC_FUNCTIONS(Plat)
