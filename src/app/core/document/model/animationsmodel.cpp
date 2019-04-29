#include "animationsmodel.h"

TAnimationsModel::TAnimationsModel(QObject *parent) :
    QAbstractTableModel(parent)
{

}

TAnimationsModel::~TAnimationsModel()
{

}

void TAnimationsModel::readFromStream(QDataStream &stream)
{
    int animationAmount;
    stream >> animationAmount;

    mAnimationList.clear();
    for(int i=0;i<animationAmount;i++) {
        TAnimation *animation = new TAnimation(this);
        animation->readFromStream(stream);
        mAnimationList.append(animation);
    }
}

void TAnimationsModel::saveToStream(QDataStream &) const
{

}

int TAnimationsModel::rowCount(const QModelIndex &) const
{
    return mAnimationList.size();
}

int TAnimationsModel::columnCount(const QModelIndex &) const
{
    return 1;
}

QVariant TAnimationsModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid()) {
        if(role == Qt::DisplayRole) {
            return tr("Animation %1").arg(index.row());
        }
    }
    return QVariant();
}

void TAnimationsModel::clear()
{
    mAnimationList.clear();
}

TAnimationList TAnimationsModel::animationList() const
{
    return mAnimationList;
}

void TAnimationsModel::setAnimationList(const TAnimationList &animationList)
{
    mAnimationList = animationList;
}
