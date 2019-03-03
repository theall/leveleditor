#include "areasmodel.h"

TAreasModel::TAreasModel(QObject *parent) :
    QAbstractTableModel(parent)
{

}

void TAreasModel::clear()
{
    mAreasList.clear();
}

void TAreasModel::readFromStream(QDataStream &stream)
{
    int areaAmount = 0;
    stream >> areaAmount;
    mAreasList.clear();

    for(int i=0;i<areaAmount;i++) {
        TArea *area = new TArea(this);
        area->readFromStream(stream);
        mAreasList.append(area);
    }
}

void TAreasModel::saveToStream(QDataStream &stream) const
{

}

int TAreasModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mAreasList.size();
}

int TAreasModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant TAreasModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole)
    if(index.isValid()) {
        int row = index.row();
        if(row>=0 && row<mAreasList.size()) {
            return tr("Area %d").arg(row+1);
        }
    }
    return QVariant();
}

