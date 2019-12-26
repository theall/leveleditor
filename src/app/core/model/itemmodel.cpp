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


TItemId *TItemModel::getCurrentItemId() const
{
    if(mCurrentIndex<0 || mCurrentIndex>=mItemIdList.size())
        return nullptr;

    return mItemIdList.at(mCurrentIndex);
}

void TItemModel::setItemList(const TItemIdList &itemIdList)
{
    mItemIdList = itemIdList;
}

int TItemModel::getCurrentIndex() const
{
    return mCurrentIndex;
}

void TItemModel::setCurrentIndex(int currentIndex)
{
    mCurrentIndex = currentIndex;
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
