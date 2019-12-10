#include "tilelayermodel.h"
#include "basemodel.h"

#include <utils/macro.h>

TTileModel::TTileModel(QObject *parent) :
    TBaseModel(TBaseModel::TILE, parent)
{

}

TTileModel::~TTileModel()
{
    FREE_CONTAINER(mTileList);
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
    stream << mTileList.size();

    for(TTile *tile : mTileList) {
        tile->saveToStream(stream);
    }
}

int TTileModel::rowCount(const QModelIndex &) const
{
    return mTileList.size();
}

void TTileModel::readFromStream(QDataStream &stream)
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

TTileList TTileModel::tileList() const
{
    return mTileList;
}

int TTileModel::tileSize() const
{
    return mTileList.size();
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
    if(index<0 || index>=mTileList.size())
        return nullptr;

    return mTileList.at(index);
}

int TTileModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 1;
}

QVariant TTileModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row>=0 && row<mTileList.size())
    {
        if(role == Qt::DisplayRole) {
            return tr("tile%1").arg(row);
        } else if(role == Qt::DecorationRole) {
            TTile *tile = mTileList.at(row);
            return tile->pixmap();
        }
    }

    return QVariant();
}

IMPL_GENERIC_FUNCTIONS(Tile)
