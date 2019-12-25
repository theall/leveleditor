#include "tilelayermodel.h"
#include "basemodel.h"

#include <utils/macro.h>

TTileModel::TTileModel(QObject *parent) :
    TGenericModel<TTile>(TBaseModel::TILE, parent)
{

}

TTileModel::~TTileModel()
{
    FREE_CONTAINER(mObjectList);
}

TTileModel::LayerType TTileModel::layerType() const
{
    return mLayerType;
}

void TTileModel::setLayerType(const LayerType &layerType)
{
    mLayerType = layerType;
}

void TTileModel::saveToStream(QDataStream &stream) const
{
    stream << mObjectList.size();

    for(TTile *tile : mObjectList) {
        tile->saveToStream(stream);
    }
}

int TTileModel::rowCount(const QModelIndex &parent) const
{
    if(!parent.isValid()) {
        return mObjectList.size();
    }
    return 0;
}

void TTileModel::readFromStream(QDataStream &stream)
{
    int tileAmount = 0;
    FREE_CONTAINER(mObjectList);
    stream >> tileAmount;
    for(int i=0;i<tileAmount;i++) {
        TTile *tile = new TTile(this);
        tile->readFromStream(stream);
        mObjectList.append(tile);
    }

    // Process tile target
    for(TTile *tile : mObjectList) {
        int tileTarget = tile->targetNumber();
        if(tileTarget>=0 && tileTarget<mObjectList.size()) {
            tile->setTarget(mObjectList.at(tileTarget));
        }
    }
}

TTileList TTileModel::tileList() const
{
    return mObjectList;
}

int TTileModel::tileSize() const
{
    return mObjectList.size();
}

TTile *TTileModel::createTile(TTileId *tileId, const QPointF &pos)
{
    TTile *tile = new TTile(this);
    tile->setTileId(tileId);
    tile->setPos(pos);
    return tile;
}

TTile *TTileModel::getTile(int index) const
{
    if(index<0 || index>=mObjectList.size())
        return nullptr;

    return mObjectList.at(index);
}

int TTileModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 1;
}

QVariant TTileModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row>=0 && row<mObjectList.size())
    {
        if(role == Qt::DisplayRole) {
            return tr("tile%1").arg(row+1);
        }
    }

    return QVariant();
}

void TTileModel::onObjectInserted(const TObjectList &objectList, const QList<int> &indexList)
{
    emit objectInserted(convert(objectList), indexList);
}

void TTileModel::onObjectRemoved(const TObjectList &objectList, const QList<int> &indexList)
{
    emit objectRemoved(convert(objectList), indexList);
}
