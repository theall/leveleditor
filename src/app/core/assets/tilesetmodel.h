#ifndef TTILESETMODEL_H
#define TTILESETMODEL_H

#include <QList>
#include <QAbstractListModel>
#include "tileset.h"

class TTilesetModel : public QAbstractListModel
{
public:
    TTilesetModel(TTileset *tileset, QObject *parent = Q_NULLPTR);
    ~TTilesetModel();

    TTileset *tileset() const;
    void setTileset(TTileset *tileset);

private:
    int mColumns;
    int mRows;
    TTileset *mTileset;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
};
typedef QList<TTilesetModel*> TTilesetModelList;

#endif // TTILESETMODEL_H
