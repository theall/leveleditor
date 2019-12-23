#include "charactermodel.h"

TCharacterModel::TCharacterModel(QObject *parent) :
    QAbstractListModel(parent)
{

}

TCharacterModel::~TCharacterModel()
{

}

TFaceList TCharacterModel::faceList() const
{
    return mFaceList;
}

TFaceId *TCharacterModel::getCurrentFaceId() const
{
    if(mCurrentIndex<0 || mCurrentIndex>=mFaceList.size())
        return nullptr;
    return mFaceList.at(mCurrentIndex);
}

void TCharacterModel::setFaceList(const TFaceList &faceList)
{
    mFaceList = faceList;
}

int TCharacterModel::getCurrentIndex() const
{
    return mCurrentIndex;
}

void TCharacterModel::setCurrentIndex(int currentIndex)
{
    mCurrentIndex = currentIndex;
}

int TCharacterModel::rowCount(const QModelIndex &) const
{
    return mFaceList.size();
}

QVariant TCharacterModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DecorationRole) {
        if(TFaceId *faceId = mFaceList.at(index.row()))
            return faceId->pixmap()->content();
    }
    return QVariant();
}
