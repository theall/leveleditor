#include "areamodel.h"

TAreaModel::TAreaModel(QObject *parent) :
    TGenericModel<TArea>(TBaseModel::AREA, parent)
{
    setName(tr("Area"));
}

TAreaModel::~TAreaModel()
{

}

void TAreaModel::clear()
{
    mObjectList.clear();
}

void TAreaModel::readFromStream(QDataStream &stream)
{
    int areaAmount = 0;
    stream >> areaAmount;
    mObjectList.clear();

    for(int i=0;i<areaAmount;i++) {
        TArea *area = new TArea(this);
        area->readFromStream(stream);
        mObjectList.append(area);
    }
}

void TAreaModel::saveToStream(QDataStream &stream) const
{
    stream << mObjectList.size();
    for(TArea *area : mObjectList) {
        area->saveToStream(stream);
    }
}

void TAreaModel::onObjectInserted(const TObjectList &objectList, const QList<int> &indexList)
{
    emit objectInserted(convert(objectList), indexList);
}

void TAreaModel::onObjectRemoved(const TObjectList &objectList, const QList<int> &indexList)
{
    emit objectRemoved(convert(objectList), indexList);
}

int TAreaModel::rowCount(const QModelIndex &parent) const
{
    if(!parent.isValid()) {
       return mObjectList.size();
    }
    return 0;

}

int TAreaModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant TAreaModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row>=0 && row<mObjectList.size())
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
    for(TArea *area : mObjectList) {
        area->setPlatNameList(platNames);
    }
}

TAreaList TAreaModel::areaList() const
{
    return mObjectList;
}

TArea *TAreaModel::createArea(const QRect &rect)
{
    return new TArea(rect, this);
}

TArea *TAreaModel::createArea(const QRectF &rect)
{
    return new TArea(rect.toRect(), this);
}
