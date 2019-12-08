#include "itemmodel.h"


TItemModel::TItemModel(QObject *parent) :
    QAbstractListModel(parent)
{

}

TItemModel::~TItemModel()
{

}

TItemIdList TItemModel::itemIdList() const
{
    return mItemIdList;
}

void TItemModel::setItemList(const TItemIdList &itemIdList)
{
    mItemIdList = itemIdList;
}

int TItemModel::rowCount(const QModelIndex &) const
{
    return mItemIdList.size();
}

QVariant TItemModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DecorationRole) {
        if(TItemId *itemId = mItemIdList.at(index.row()))
            return itemId->pixmap()->content();
    }
    return QVariant();
}
