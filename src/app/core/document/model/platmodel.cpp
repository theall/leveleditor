#include "platmodel.h"
#include "basemodel.h"

TPlatModel::TPlatModel(QObject *parent) :
    TGenericModel<TPlat>(TBaseModel::PLAT, parent)
{
    setName(tr("Platform"));
    setIcon(QIcon(":/scenemodel/images/platform.png"));
}

void TPlatModel::readFromStream(QDataStream &stream)
{
    int platAmount;
    stream >> platAmount;
    mObjectList.clear();
    for(int i=0;i<platAmount;i++) {
        TPlat *plat = new TPlat(this);
        plat->readFromStream(stream);
        mObjectList.append(plat);
    }
}

void TPlatModel::saveToStream(QDataStream &stream) const
{
    stream << mObjectList.size();

    for(TPlat *plat : mObjectList) {
        plat->saveToStream(stream);
    }
}

int TPlatModel::rowCount(const QModelIndex &parent) const
{
    if(!parent.isValid()) {
       return mObjectList.size();
    }
    return 0;
}

int TPlatModel::columnCount(const QModelIndex &) const
{
    return 1;
}

QVariant TPlatModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row>=0 && row<mObjectList.size())
    {
        if(role==Qt::DisplayRole)
        {
            return tr("Platform %1").arg(row+1);
        }
    }
    return QVariant();
}

TPlatList TPlatModel::platList() const
{
    return mObjectList;
}

QStringList TPlatModel::getPlatNames() const
{
    QStringList platNames;
    int i = 1;
    for(TPlat *plat : mObjectList) {
        if(!plat)
            continue;

        platNames.append(tr("Plat%1").arg(i++));
    }
    return platNames;
}

TPlat *TPlatModel::getPlat(int index) const
{
    return getObject(index);
}

void TPlatModel::clear()
{
    mObjectList.clear();
}

TPlat *TPlatModel::createPlat()
{
    return new TPlat(this);
}

void TPlatModel::onObjectInserted(const TObjectList &objectList, const QList<int> &indexList)
{
    emit objectInserted(convert(objectList), indexList);
}

void TPlatModel::onObjectRemoved(const TObjectList &objectList, const QList<int> &indexList)
{
    emit objectRemoved(convert(objectList), indexList);
}

void TPlatModel::onObjectMove(const TObjectList &objectList, const QList<int> &posList)
{

}
