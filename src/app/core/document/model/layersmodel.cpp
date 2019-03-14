#include "layersmodel.h"

#include <QColor>

static const int COLUMN_FRAMES_COUNT = 0;
static const int COLUMN_LAYER_NAME = 1;

TLayersModel::TLayersModel(QObject *parent) :
    QAbstractTableModel(parent)
{

}

TLayersModel::~TLayersModel()
{
    clear();
}

void TLayersModel::saveToStream(QDataStream &stream) const
{
    for(TLayer *layer : mLayerList)
    {
        layer->saveToStream(stream);
    }
}

void TLayersModel::clear()
{
}

void TLayersModel::readFromStream(QDataStream &stream)
{

}

QList<TLayer *> TLayersModel::layerList() const
{
    return mLayerList;
}

int TLayersModel::addLayer(const QString &name)
{
    return addLayer(new TLayer(name, this));
}

int TLayersModel::addLayer(TLayer *layer, int index)
{
    if(index < 0) {
        mLayerList.append(layer);
        index = mLayerList.size() - 1;
    } else {
        mLayerList.insert(index, layer);
    }
    emit layoutChanged();
    return index;
}

int TLayersModel::removeLayer(TLayer *layer)
{
    QList<TLayer *> layerList;
    layerList.append(layer);
    QList<int> indexRemoved = removeLayers(layerList);
    if(indexRemoved.size() > 0)
        return indexRemoved.first();
    return -1;
}

int TLayersModel::removeLayer(int index)
{
    QList<int> layerIndexList;
    layerIndexList.append(index);
    QList<int> indexRemoved = removeLayers(layerIndexList);
    if(indexRemoved.size() > 0)
        return indexRemoved.first();
    return -1;
}

QList<int> TLayersModel::removeLayers(const QList<TLayer *> &layers)
{
    QList<int> removedIndex;
    for(TLayer *layer : layers)
    {
        int i = mLayerList.indexOf(layer);
        if(i != -1) {
            layer->disconnect(this);
            mLayerList.removeAt(i);
            removedIndex.append(i);
        }
    }
    if(removedIndex.size() > 0)
        emit layoutChanged();

    return removedIndex;
}

QList<int> TLayersModel::removeLayers(const QList<int> &layerList)
{
    QList<TLayer*> realLayerList;
    for(int index : layerList)
    {
        TLayer *layer = getLayer(index);
        if(layer)
            realLayerList.append(layer);
    }
    return removeLayers(realLayerList);
}

TLayer *TLayersModel::getLayer(int index)
{
    if(index>=0 && index<mLayerList.size())
        return mLayerList.at(index);
    return nullptr;
}

int TLayersModel::count()
{
    return mLayerList.count();
}

void TLayersModel::render(QPainter *painter, const QRectF &rect)
{
    foreach (TLayer *layer, mLayerList) {
        layer->render(painter, rect);
    }
}

void TLayersModel::slotLayerNameChanged(const QString &newName)
{
    Q_UNUSED(newName);

    emit layoutChanged();
}

TLayer *TLayersModel::getLayer(const QModelIndex &index)
{
    return getLayer(index.row());
}

int TLayersModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return mLayerList.size();
}

int TLayersModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 2;
}

QVariant TLayersModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row>=0 && row<mLayerList.size())
    {
        int col = index.column();
        TLayer *layer = mLayerList.at(row);
        if(role==Qt::DisplayRole)
        {
            if(col==COLUMN_FRAMES_COUNT)
                return QString("(%1)").arg(0);
            else if(col==COLUMN_LAYER_NAME)
                return layer->name();
        } else if (role==Qt::EditRole) {
            return layer->name();
        } else if(role==Qt::TextColorRole) {
            if(col==COLUMN_FRAMES_COUNT)
                return QColor(Qt::blue);
        }
    }
    return QVariant();
}

Qt::ItemFlags TLayersModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags f = QAbstractTableModel::flags(index);
    if(index.column() == COLUMN_LAYER_NAME)
        f |= Qt::ItemIsEditable;
    return f;
}

bool TLayersModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.column()==COLUMN_LAYER_NAME && role==Qt::EditRole)
    {
        TLayer *layer = getLayer(index);
        if(layer)
        {
            layer->setName(value.toString());
            return true;
        }
    }
    return false;
}
