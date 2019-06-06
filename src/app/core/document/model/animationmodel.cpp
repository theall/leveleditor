#include "animationmodel.h"

TAnimationModel::TAnimationModel(QObject *parent) :
    TBaseModel(TBaseModel::ANIMATION, parent)
{
    setName(tr("Animation"));
}

TAnimationModel::~TAnimationModel()
{

}

void TAnimationModel::readFromStream(QDataStream &stream)
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

void TAnimationModel::saveToStream(QDataStream &stream) const
{
    stream << mAnimationList.size();

    for(TAnimation *animation : mAnimationList) {
        animation->saveToStream(stream);
    }
}

int TAnimationModel::rowCount(const QModelIndex &) const
{
    return mAnimationList.size();
}

int TAnimationModel::columnCount(const QModelIndex &) const
{
    return 1;
}

QVariant TAnimationModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid()) {
        if(role == Qt::DisplayRole) {
            return tr("Animation %1").arg(index.row());
        }
    }
    return QVariant();
}

void TAnimationModel::clear()
{
    mAnimationList.clear();
}

TAnimationList TAnimationModel::animationList() const
{
    return mAnimationList;
}

void TAnimationModel::setAnimationList(const TAnimationList &animationList)
{
    mAnimationList = animationList;
}
