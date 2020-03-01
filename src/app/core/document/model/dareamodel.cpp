#include "dareamodel.h"

TDAreaModel::TDAreaModel(QObject *parent) :
    TGenericModel<TDArea>(TBaseModel::DAREA, parent)
{
    setName(tr("Danger Area"));
     setIcon(QIcon(":/scenemodel/images/danger-area.png"));
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
    mObjectList.clear();

    for(int i=0;i<areaAmount;i++) {
        TDArea *area = new TDArea(this);
        area->readFromStream(stream);
        mObjectList.append(area);
    }
}

void TDAreaModel::saveToStream(QDataStream &stream) const
{
    stream << mObjectList.size();

    for(TDArea *area : mObjectList) {
        area->saveToStream(stream);
    }
}

int TDAreaModel::rowCount(const QModelIndex &parent) const
{
    if(!parent.isValid()) {
       return mObjectList.size();
    }
    return 0;
}

int TDAreaModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant TDAreaModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row>=0 && row<mObjectList.size())
    {
        if(role==Qt::DisplayRole)
        {
            return tr("Danger Area %1").arg(row+1);
        }
    }
    return QVariant();
}

void TDAreaModel::onObjectInserted(const TObjectList &objectList, const QList<int> &indexList)
{
    emit objectInserted(convert(objectList), indexList);
}

void TDAreaModel::onObjectRemoved(const TObjectList &objectList, const QList<int> &indexList)
{
    emit objectRemoved(convert(objectList), indexList);
}

void TDAreaModel::onObjectMove(const TObjectList &objectList, const QList<int> &posList)
{

}

TDAreaList TDAreaModel::dAreaList() const
{
    return mObjectList;
}

void TDAreaModel::setDAreaList(const TDAreaList &dAreaList)
{
    mObjectList = dAreaList;
}
