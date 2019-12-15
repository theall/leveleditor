#include "shotmodel.h"

TShotModel::TShotModel(QObject *parent) :
    QAbstractListModel(parent)
{

}

TShotModel::~TShotModel()
{

}

TShotList TShotModel::shotIdList() const
{
    return mShotList;
}

void TShotModel::setShotIdList(const TShotList &shotidList)
{
    mShotList = shotidList;
}

int TShotModel::rowCount(const QModelIndex &) const
{
    return mShotList.size();
}

QVariant TShotModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DecorationRole) {
        if(TShotId *shotId = mShotList.at(index.row()))
            return shotId->pixmap()->content();
    }
    return QVariant();
}
