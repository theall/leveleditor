#include "framemodel.h"

TFrameModel::TFrameModel(QObject *parent) :
    TBaseModel(TBaseModel::FRAME, parent)
  , mAnimation(nullptr)
{
    setName(tr("FrameModel"));
}

TFrameModel::~TFrameModel()
{

}

void TFrameModel::readFromStream(QDataStream &stream)
{
    if(mAnimation) {
        delete mAnimation;
        mAnimation = nullptr;
    }

    mAnimation = new TAnimation(this);
    mAnimation->readFromStream(stream);
}

void TFrameModel::saveToStream(QDataStream &stream) const
{
    if(!mAnimation)
        return;

    mAnimation->saveToStream(stream);
}

int TFrameModel::rowCount(const QModelIndex &) const
{
    return 1;
}

int TFrameModel::columnCount(const QModelIndex &) const
{
    return mAnimation->getFrameSize();
}

QVariant TFrameModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid()) {
        int col = index.column();
        if(col>=0 && col<mAnimation->getFrameSize()) {
            if(role == Qt::DisplayRole) {
                return tr("%1").arg(col+1);
            } else if(role == Qt::DecorationRole) {
                return mAnimation->getFramePixmap(col);
            }
        }
    }
    return QVariant();
}

void TFrameModel::clear()
{
    mAnimation->clear();
}

TAnimation *TFrameModel::animation() const
{
    return mAnimation;
}

void TFrameModel::setAnimation(TAnimation *animation)
{
    mAnimation = animation;
}

QIcon TFrameModel::getIcon() const
{
    return mAnimation?mAnimation->getIcon():QIcon();
}

TPropertySheet *TFrameModel::getPropertySheet() const
{
    return mAnimation?mAnimation->propertySheet():nullptr;
}

TPropertySheet *TFrameModel::getFramePropertySheet(int index) const
{
    return mAnimation?mAnimation->getFramePropertySheet(index):nullptr;
}

TFrame *TFrameModel::getFrame(int index) const
{
    return mAnimation?mAnimation->getFrame(index):nullptr;
}