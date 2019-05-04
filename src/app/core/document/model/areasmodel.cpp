#include "areasmodel.h"

TAreasModel::TAreasModel(QObject *parent) :
    TBaseModel(parent)
{
    setName(tr("Area"));
}

void TAreasModel::clear()
{
    mAreaList.clear();
}

void TAreasModel::readFromStream(QDataStream &stream)
{
    int areaAmount = 0;
    stream >> areaAmount;
    mAreaList.clear();

    for(int i=0;i<areaAmount;i++) {
        TArea *area = new TArea(this);
        area->readFromStream(stream);
        mAreaList.append(area);
    }
}

void TAreasModel::saveToStream(QDataStream &stream) const
{

}

int TAreasModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mAreaList.size();
}

int TAreasModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant TAreasModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row>=0 && row<mAreaList.size())
    {
        if(role==Qt::DisplayRole)
        {
            return tr("Area (%1)").arg(mAreaList.at(row)->toString());
        }
    }
    return QVariant();
}

TAreaList TAreasModel::areaList() const
{
    return mAreaList;
}

