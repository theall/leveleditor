#include "tilesetmodel.h"

TTilesetModel::TTilesetModel(TTileset *tileset, QObject *parent) :
    QAbstractListModel(parent)
  , mTileset(tileset)
  , mCurrentIndex(0)
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

TTileId *TTilesetModel::getCurrentTileId() const
{
    return mTileset->getTileId(mCurrentIndex);
}

int TTilesetModel::getCurrentIndex() const
{
    return mCurrentIndex;
}

void TTilesetModel::setCurrentIndex(int currentIndex)
{
    mCurrentIndex = currentIndex;
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

TTilesetModelManager::TTilesetModelManager(QObject *parent) :
    QObject(parent)
  , mCurrentIndex(0)
{

}

TTilesetModelManager::~TTilesetModelManager()
{

}

TTilesetModelList TTilesetModelManager::tilsetModelList() const
{
    return mTilsetModelList;
}

void TTilesetModelManager::setTilsetModelList(const TTilesetModelList &tilsetModelList)
{
    mTilsetModelList = tilsetModelList;
}

int TTilesetModelManager::currentIndex() const
{
    return mCurrentIndex;
}

void TTilesetModelManager::setCurrentIndex(int currentIndex)
{
    mCurrentIndex = currentIndex;
}

void TTilesetModelManager::setCurrentIndex(int tilesetIndex, int tileIndex)
{
    mCurrentIndex = tilesetIndex;
    TTilesetModel *tilesetModel = mTilsetModelList.at(tilesetIndex);
    if(tilesetModel)
        tilesetModel->setCurrentIndex(tileIndex);
}

TTilesetModel *TTilesetModelManager::currentTilesetModel() const
{
    return mTilsetModelList.at(mCurrentIndex);
}

TTilesetModel *TTilesetModelManager::getTilesetModel(int index) const
{
    return mTilsetModelList.at(index);
}

TTileId *TTilesetModelManager::getCurrentTileId() const
{
    TTileId *tileId = nullptr;
    TTilesetModel *currentModel = mTilsetModelList.at(mCurrentIndex);
    if(currentModel) {
        tileId = currentModel->getCurrentTileId();
    }
    return tileId;
}

TTileId *TTilesetModelManager::getTileId(int tileset, int index) const
{
    TTilesetModel *tilesetModel =  mTilsetModelList.at(tileset);
    if(!tilesetModel)
        return nullptr;

    return tilesetModel->getTileId(index);
}

TTilesetModelList TTilesetModelManager::getTilsetModelList() const
{
    return mTilsetModelList;
}
