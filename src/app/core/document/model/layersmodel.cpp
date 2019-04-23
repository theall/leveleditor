#include "layersmodel.h"

#include <QColor>
#include <utils/macro.h>

#define COLUMN_ITEMS_COUNT 0
#define COLUMN_LAYER_NAME 1

TLayersModel::TLayersModel(QObject *parent) :
    QAbstractTableModel(parent)
{

}

TLayersModel::~TLayersModel()
{

}

TLayerList TLayersModel::getForegroundLayerList() const
{
    return mForegroundLayerList;
}

TLayerList TLayersModel::getBackgroundLayerList() const
{
    return mBackgroundLayerList;
}

void TLayersModel::saveToStream(QDataStream &stream) const
{
    for(TLayer *layer : mUnityLayerList)
    {
        layer->saveToStream(stream);
    }
}

int TLayersModel::rowCount(const QModelIndex &) const
{
    return mUnityLayerList.size();
}

void TLayersModel::readFromStream(QDataStream &stream)
{
   mBackgroundLayerList.clear();
    for(int i=0;i<3;i++) {
        TLayer *layer = new TLayer(this);
        layer->setName(tr("Background Layer"));
        layer->readFromStream(stream);
        mBackgroundLayerList.append(layer);
    }

    mForegroundLayerList.clear();
    for(int i=0;i<3;i++) {
        TLayer *layer = new TLayer(this);
        layer->setType(TLayer::Foreground);
        layer->setName(tr("Foreground Layer"));
        layer->readFromStream(stream);
        mForegroundLayerList.append(layer);
    }

    FREE_CONTAINER(mUnityLayerList);
    mUnityLayerList = mBackgroundLayerList + mForegroundLayerList;
}

int TLayersModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 2;
}

QVariant TLayersModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row>=0 && row<mUnityLayerList.size())
    {
        int col = index.column();
        TLayer *layer = mUnityLayerList.at(row);
        if(role==Qt::DisplayRole)
        {
            if(col==COLUMN_ITEMS_COUNT)
                return QString("(%1)").arg(0);
            else if(col==COLUMN_LAYER_NAME)
                return layer->name();
        }
    }
    return QVariant();
}
