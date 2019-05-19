#ifndef TTILESETMODEL_H
#define TTILESETMODEL_H

#include <QList>
#include <QAbstractListModel>
#include "../assets/tileset.h"

class TTilesetModel : public QAbstractListModel
{
public:
    explicit TTilesetModel(TTileset *tileset, QObject *parent = Q_NULLPTR);
    ~TTilesetModel();

    TTileset *tileset() const;
    void setTileset(TTileset *tileset);

    TTileId *getTileId(int index) const;
    TTileId *getCurrentTileId() const;

    int getCurrentIndex() const;
    void setCurrentIndex(int currentIndex);

private:
    TTileset *mTileset;
    int mCurrentIndex;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
};
typedef QList<TTilesetModel*> TTilesetModelList;

class TTilesetModelManager : public QObject
{
public:
    explicit TTilesetModelManager(QObject *parent = Q_NULLPTR);
    ~TTilesetModelManager();

    TTilesetModelList tilsetModelList() const;
    void setTilsetModelList(const TTilesetModelList &tilsetModelList);

    int currentIndex() const;
    void setCurrentIndex(int currentIndex);
    void setCurrentIndex(int tilesetIndex, int tileIndex);

    TTilesetModel *currentTilesetModel() const;
    TTilesetModel *getTilesetModel(int index) const;

    TTileId *getCurrentTileId() const;
    TTileId *getTileId(int tileset, int index) const;

    TTilesetModelList getTilsetModelList() const;

private:
    int mCurrentIndex;
    TTilesetModelList mTilsetModelList;
};

#endif // TTILESETMODEL_H
