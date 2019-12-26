#include "chunkmodel.h"

TChunkModel::TChunkModel(QObject *parent) :
  QAbstractListModel(parent)
{

}

TChunkModel::~TChunkModel()
{

}

TChunkList TChunkModel::chunIdList() const
{
    return mChunkList;
}

void TChunkModel::setChunIdList(const TChunkList &chunidList)
{
    mChunkList = chunidList;
}

void TChunkModel::setCurrentIndex(int currentIndex)
{
    mCurrentIndex = currentIndex;
}

TChunkId *TChunkModel::getCurrentChunkId() const
{
    if(mCurrentIndex<0 || mCurrentIndex>=mChunkList.size())
        return nullptr;

    return mChunkList.at(mCurrentIndex);
}

int TChunkModel::rowCount(const QModelIndex &) const
{
    return mChunkList.size();
}

QVariant TChunkModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DecorationRole) {
        if(TChunkId *chunId = mChunkList.at(index.row()))
            return chunId->pixmap()->content();
    }
    return QVariant();
}
