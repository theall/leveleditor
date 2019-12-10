#include "dareamodel.h"

TDAreaModel::TDAreaModel(QObject *parent) :
    TBaseModel(TBaseModel::DAREA, parent)
{
    setName(tr("Danger Area"));
}

TDAreaModel::~TDAreaModel()
{

}

void TDAreaModel::clear()
{

}

void TDAreaModel::readFromStream(QDataStream &stream)
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

void TDAreaModel::saveToStream(QDataStream &stream) const
{
    stream << mDAreaList.size();

    for(TDArea *area : mDAreaList) {
        area->saveToStream(stream);
    }
}

int TDAreaModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mDAreaList.size();
}

int TDAreaModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant TDAreaModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row>=0 && row<mDAreaList.size())
    {
        if(role==Qt::DisplayRole)
        {
            return tr("Danger Area %1").arg(row+1);
        }
    }
    return QVariant();
}

TDAreaList TDAreaModel::dAreaList() const
{
    return mDAreaList;
}

void TDAreaModel::setDAreaList(const TDAreaList &dAreaList)
{
    mDAreaList = dAreaList;
}

IMPL_GENERIC_FUNCTIONS(DArea)
