#include "tilelayermodel.h"

TTileLayerModel::TTileLayerModel(QObject *parent) :
    TBaseModel(parent)
  , mLayer(new TLayer(this))
{

}

TTileLayerModel::~TTileLayerModel()
{

}

TLayer *TTileLayerModel::layer() const
{
    return mLayer;
}

void TTileLayerModel::saveToStream(QDataStream &stream) const
{
    mLayer->saveToStream(stream);
}

int TTileLayerModel::rowCount(const QModelIndex &) const
{
    return mLayer->tileSize();
}

void TTileLayerModel::readFromStream(QDataStream &stream)
{
    mLayer->readFromStream(stream);
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
        if(row>=0 && row<mLayer->tileList().size())
        {

        }
    }

    return QVariant();
}
