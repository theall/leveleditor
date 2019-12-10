#include "wallmodel.h"

TWallModel::TWallModel(QObject *parent) :
    TBaseModel(TBaseModel::WALL, parent)
{
    setName(tr("Wall"));
}

void TWallModel::readFromStream(QDataStream &stream)
{
    int wallAmount = 0;
    stream >> wallAmount;
    mWallList.clear();
    for(int i=0;i<wallAmount;i++) {
        TWall *wall = new TWall(this);
        wall->readFromStream(stream);
        mWallList.append(wall);
    }
}

void TWallModel::saveToStream(QDataStream &stream) const
{
    stream << mWallList.size();
    for(TWall *wall : mWallList) {
        wall->saveToStream(stream);
    }
}

int TWallModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mWallList.size();
}

int TWallModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant TWallModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row>=0 && row<mWallList.size())
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
    return mWallList;
}

void TWallModel::clear()
{
    mWallList.clear();
}

IMPL_GENERIC_FUNCTIONS(Wall)
