#include "wallmodel.h"

TWallModel::TWallModel(QObject *parent) :
    TGenericModel<TWall>(TBaseModel::ANIMATION, parent)
{
    setName(tr("Wall"));
}

void TWallModel::readFromStream(QDataStream &stream)
{
    int wallAmount = 0;
    stream >> wallAmount;
    mObjectList.clear();
    for(int i=0;i<wallAmount;i++) {
        TWall *wall = new TWall(this);
        wall->readFromStream(stream);
        mObjectList.append(wall);
    }
}

void TWallModel::saveToStream(QDataStream &stream) const
{
    stream << mObjectList.size();
    for(TWall *wall : mObjectList) {
        wall->saveToStream(stream);
    }
}

int TWallModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mObjectList.size();
}

int TWallModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant TWallModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row>=0 && row<mObjectList.size())
    {
        if(role==Qt::DisplayRole)
        {
            return tr("Wall %1").arg(row+1);
        }
    }
    return QVariant();
}

TWallList TWallModel::wallList() const
{
    return mObjectList;
}

void TWallModel::clear()
{
    mObjectList.clear();
}

void TWallModel::onObjectInserted(const TObjectList &, const QList<int> &indexList)
{
    emit objectInserted(mObjectList, indexList);
}

void TWallModel::onObjectRemoved(const TObjectList &, const QList<int> &indexList)
{
    emit objectRemoved(mObjectList, indexList);
}
