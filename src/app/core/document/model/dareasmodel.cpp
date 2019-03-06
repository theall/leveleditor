#include "dareasmodel.h"

TDAreasModel::TDAreasModel(QObject *parent) :
    QAbstractTableModel(parent)
{

}

void TDAreasModel::clear()
{

}

void TDAreasModel::readFromStream(QDataStream &stream)
{
    int areaAmount = 0;
    stream >> areaAmount;
    mDAreaList.clear();

    for(int i=0;i<areaAmount;i++) {
        TDArea *area = new TDArea(this);
        area->readFromStream(stream);
        mDAreaList.append(area);
    }
}

void TDAreasModel::saveToStream(QDataStream &stream) const
{

}

int TDAreasModel::rowCount(const QModelIndex &parent) const
{
    return mDAreaList.size();
}

int TDAreasModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant TDAreasModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row>=0 && row<mDAreaList.size())
    {
        if(role==Qt::DisplayRole)
        {
            return tr("Danger Area %d").arg(row+1);
        }
    }
    return QVariant();
}
