#include "wallsmodel.h"

TWallsModel::TWallsModel(QObject *parent) :
    TBaseModel(parent)
{
    setName(tr("Wall"));
}

void TWallsModel::readFromStream(QDataStream &stream)
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

void TWallsModel::saveToStream(QDataStream &stream) const
{

}

int TWallsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mWallList.size();
}

int TWallsModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant TWallsModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row>=0 && row<mWallList.size())
    {
        if(role==Qt::DisplayRole)
        {
            return tr("Wall %d").arg(row+1);
        }
    }
    return QVariant();
}

TWallList TWallsModel::wallList() const
{
    return mWallList;
}

void TWallsModel::clear()
{
    mWallList.clear();
}
