#include "areamodel.h"

TAreaModel::TAreaModel(QObject *parent) :
    TBaseModel(TBaseModel::AREA, parent)
{
    setName(tr("Area"));
}

TAreaModel::~TAreaModel()
{

}

void TAreaModel::clear()
{
    mAreaList.clear();
}

void TAreaModel::readFromStream(QDataStream &stream)
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

void TAreaModel::saveToStream(QDataStream &stream) const
{
    stream << mAreaList.size();
    for(TArea *area : mAreaList) {
        area->saveToStream(stream);
    }
}

int TAreaModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mAreaList.size();
}

int TAreaModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant TAreaModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row>=0 && row<mAreaList.size())
    {
        if(role==Qt::DisplayRole)
        {
            return tr("Area %1").arg(row+1);
        }
    }
    return QVariant();
}

void TAreaModel::setPlatNameList(const QStringList &platNames)
{
    for(TArea *area : mAreaList) {
        area->setPlatNameList(platNames);
    }
}

TAreaList TAreaModel::areaList() const
{
    return mAreaList;
}

TArea *TAreaModel::createArea(const QRect &rect)
{
    return new TArea(rect, this);
}

TArea *TAreaModel::createArea(const QRectF &rect)
{
    return new TArea(rect.toRect(), this);
}

IMPL_GENERIC_FUNCTIONS(Area)
