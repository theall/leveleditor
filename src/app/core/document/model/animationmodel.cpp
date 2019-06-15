#include "animationmodel.h"

TAnimationModel::TAnimationModel(QObject *parent) :
    TBaseModel(TBaseModel::ANIMATION, parent)
{
    setName(tr("AnimationModel"));
}

TAnimationModel::~TAnimationModel()
{

}

void TAnimationModel::readFromStream(QDataStream &stream)
{
    int animationAmount;
    stream >> animationAmount;

    mFrameModelList.clear();
    for(int i=0;i<animationAmount;i++) {
        TFrameModel *frameModel = new TFrameModel(this);
        frameModel->readFromStream(stream);
        mFrameModelList.append(frameModel);
    }
}

void TAnimationModel::saveToStream(QDataStream &stream) const
{
    stream << mFrameModelList.size();

    for(TFrameModel *frameModel : mFrameModelList) {
        frameModel->saveToStream(stream);
    }
}

int TAnimationModel::rowCount(const QModelIndex &) const
{
    return mFrameModelList.size();
}

int TAnimationModel::columnCount(const QModelIndex &) const
{
    return 1;
}

QVariant TAnimationModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid()) {
        int row = index.row();
        if(row>=0 && row<mFrameModelList.size()) {
            if(role == Qt::DisplayRole) {
                return tr("Animation %1").arg(row+1);
            } else if(role == Qt::DecorationRole) {
                return mFrameModelList.at(row)->getIcon();
            }
        }
    }
    return QVariant();
}

void TAnimationModel::clear()
{
    mFrameModelList.clear();
}

TFrameModelList TAnimationModel::frameModelList() const
{
    return mFrameModelList;
}

void TAnimationModel::setFrameModelList(const TFrameModelList &frameModelList)
{
    mFrameModelList = frameModelList;
}

TFrameModel *TAnimationModel::getFrameModel(int index) const
{
    if(index<0 || index>=mFrameModelList.size())
        return nullptr;
    return mFrameModelList.at(index);
}
