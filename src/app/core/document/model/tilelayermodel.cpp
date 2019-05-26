#include "tilelayermodel.h"
#include "objectgeneric.hpp"

#include <utils/macro.h>

TTileLayerModel::TTileLayerModel(QObject *parent) :
    TBaseModel(TBaseModel::TILE, parent)
{

}

TTileLayerModel::~TTileLayerModel()
{
    FREE_CONTAINER(mTileList);
}

TTileLayerModel::LayerType TTileLayerModel::layerType() const
{
    return mLayerType;
}

void TTileLayerModel::setLayerType(const LayerType &layerType)
{
    mLayerType = layerType;
}


void TTileLayerModel::saveToStream(QDataStream &stream) const
{
    stream << mTileList.size();

    for(TTile *tile : mTileList) {
        tile->saveToStream(stream);
    }
}

int TTileLayerModel::rowCount(const QModelIndex &) const
{
    return mTileList.size();
}

void TTileLayerModel::readFromStream(QDataStream &stream)
{
    int tileAmount = 0;
    FREE_CONTAINER(mTileList);
    stream >> tileAmount;
    for(int i=0;i<tileAmount;i++) {
        TTile *tile = new TTile(this);
        tile->readFromStream(stream);
        mTileList.append(tile);
    }

    // Process tile target
    for(TTile *tile : mTileList) {
        int tileTarget = tile->targetNumber();
        if(tileTarget>=0 && tileTarget<mTileList.size()) {
            tile->setTarget(mTileList.at(tileTarget));
        }
    }
}

TTileList TTileLayerModel::tileList() const
{
    return mTileList;
}

int TTileLayerModel::tileSize() const
{
    return mTileList.size();
}

void TTileLayerModel::insertTile(TTile *tile, int index)
{
    if(!tile)
        return;

    TTileList tileList;
    QList<int> indexList;
    tileList.append(tile);
    indexList.append(index);
    insertTile(tileList, indexList);
}

void TTileLayerModel::insertTile(const TTileList &tileList, const QList<int> &indexList)
{
    TTileList tileInsertedList = tileList;
    QList<int> insertedIndexList = indexList;
    insertIntoContainer<TTile*>(mTileList, tileInsertedList, insertedIndexList);
    emit tileInserted(tileInsertedList, insertedIndexList);
}

int TTileLayerModel::removeTile(int index)
{
    QList<int> indexList;
    indexList.append(index);

    QList<int> indexRemovedList = removeTile(indexList);
    index = -1;
    if(!indexRemovedList.isEmpty())
        index = indexRemovedList.at(0);
    return index;
}

int TTileLayerModel::removeTile(TTile *tile)
{
    TTileList tileList;
    tileList.append(tile);

    QList<int> indexRemovedList = removeTile(tileList);
    int index = -1;
    if(!indexRemovedList.isEmpty())
        index = indexRemovedList.at(0);
    return index;
}

QList<int> TTileLayerModel::removeTile(const QList<int> &indexList)
{
    TTileList tileList;
    QList<int> indexRemoved = indexList;
    tileList = removeFromContainer<TTile*>(mTileList, indexRemoved);
    if(!indexRemoved.isEmpty())
        emit tileRemoved(tileList, indexRemoved);
    return indexRemoved;
}

QList<int> TTileLayerModel::removeTile(const TTileList &tileList)
{
    QList<int> indexRemoved;
    TTileList tileListRemoved = tileList;
    indexRemoved = removeFromContainer<TTile*>(mTileList, tileListRemoved);
    if(!indexRemoved.isEmpty())
        emit tileRemoved(tileList, indexRemoved);
    return indexRemoved;
}

TTile *TTileLayerModel::createTile(TTileId *tileId, const QPointF &pos)
{
    TTile *tile = new TTile(this);
    tile->setTileId(tileId);
    tile->setPos(pos);
    return tile;
}

int TTileLayerModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 2;
}

QVariant TTileLayerModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole) {
        int row = index.row();
        if(row>=0 && row<mTileList.size())
        {

        }
    }

    return QVariant();
}

void TTileLayerModel::insertObjects(const TObjectList &objectList, const QList<int> &indexList)
{
    TTileList tileList = convert<TTile*>(objectList);
    insertTile(tileList, indexList);
}

QList<int> TTileLayerModel::removeObjects(const TObjectList &objectList)
{
    TTileList tileList = convert<TTile*>(objectList);
    return removeTile(tileList);
}
