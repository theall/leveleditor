#include "tilesetmodel.h"

TTilesetModel::TTilesetModel(TTileset *tileset, QObject *parent) :
    QAbstractListModel(parent)
  , mTileset(tileset)
{
    Q_ASSERT(mTileset);
}

TTilesetModel::~TTilesetModel()
{

}

TTileset *TTilesetModel::tileset() const
{
    return mTileset;
}

void TTilesetModel::setTileset(TTileset *tileset)
{
    if (mTileset == tileset)
        return;

    beginResetModel();
    mTileset = tileset;
    endResetModel();
}

TTileId *TTilesetModel::getTileId(int index) const
{
    return mTileset->getTileId(index);
}

int TTilesetModel::rowCount(const QModelIndex &) const
{
    return mTileset->tileList().size();
}

int TTilesetModel::columnCount(const QModelIndex &) const
{
    return 1;
}

QVariant TTilesetModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DecorationRole) {
        int row = index.row();
        TTileIdList tileList = mTileset->tileList();
        if(row>=0 && row<tileList.size()) {
            TTileId *tile = tileList.at(row);
            if(TPixmap *p = tile->pixmap()) {
                return p->pixmap();
            }
        }
    }
    return QVariant();
}

Qt::ItemFlags TTilesetModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractListModel::flags(index);

    if (index.isValid())
        defaultFlags |= Qt::ItemIsDragEnabled;

    return defaultFlags;
}
