#include "areasmodel.h"
#include "objectgeneric.hpp"

TAreasModel::TAreasModel(QObject *parent) :
    TBaseModel(TBaseModel::AREA, parent)
{
    setName(tr("Area"));
}

TAreasModel::~TAreasModel()
{

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

TArea *TAreasModel::createArea(const QRect &rect)
{
    return new TArea(rect, this);
}

TArea *TAreasModel::createArea(const QRectF &rect)
{
    return new TArea(rect.toRect(), this);
}


void TAreasModel::insertArea(TArea *area, int index)
{
    if(!area)
        return;

    TAreaList areaList;
    QList<int> indexList;
    areaList.append(area);
    indexList.append(index);
    insertArea(areaList, indexList);
}

void TAreasModel::insertArea(const TAreaList &areaList, const QList<int> &indexList)
{
    TAreaList areaInsertedList = areaList;
    QList<int> insertedIndexList = indexList;
    insertIntoContainer<TArea*>(mAreaList, areaInsertedList, insertedIndexList);
    emit areaInserted(areaInsertedList, insertedIndexList);
}

int TAreasModel::removeArea(int index)
{
    QList<int> indexList;
    indexList.append(index);

    QList<int> indexRemovedList = removeArea(indexList);
    index = -1;
    if(!indexRemovedList.isEmpty())
        index = indexRemovedList.at(0);
    return index;
}

int TAreasModel::removeArea(TArea *area)
{
    TAreaList areaList;
    areaList.append(area);

    QList<int> indexRemovedList = removeArea(areaList);
    int index = -1;
    if(!indexRemovedList.isEmpty())
        index = indexRemovedList.at(0);
    return index;
}

QList<int> TAreasModel::removeArea(const QList<int> &indexList)
{
    TAreaList areaList;
    QList<int> indexRemoved = indexList;
    areaList = removeFromContainer<TArea*>(mAreaList, indexRemoved);
    if(!indexRemoved.isEmpty())
        emit areaRemoved(areaList, indexRemoved);
    return indexRemoved;
}

QList<int> TAreasModel::removeArea(const TAreaList &areaList)
{
    QList<int> indexRemoved;
    TAreaList areaListRemoved = areaList;
    indexRemoved = removeFromContainer<TArea*>(mAreaList, areaListRemoved);
    if(!indexRemoved.isEmpty())
        emit areaRemoved(areaList, indexRemoved);
    return indexRemoved;
}

void TAreasModel::insertObjects(const TObjectList &objectList, const QList<int> &indexList)
{
    TAreaList areaList = convert<TArea*>(objectList);
    insertArea(areaList, indexList);
}

QList<int> TAreasModel::removeObjects(const TObjectList &objectList)
{
    TAreaList areaList = convert<TArea*>(objectList);
    return removeArea(areaList);
}
