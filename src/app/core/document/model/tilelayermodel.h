#ifndef TTILELAYERMODEL_H
#define TTILELAYERMODEL_H

#include "basemodel.h"
#include "entity/tile.h"

class TTileLayerModel : public TBaseModel
{
    Q_OBJECT

public:
    enum LayerType {
        Background,
        Foreground
    };
    TTileLayerModel(QObject *parent = nullptr);
    ~TTileLayerModel();

    LayerType layerType() const;
    void setLayerType(const LayerType &layerType);

    TTileList tileList() const;
    int tileSize() const;

    void insertTile(TTile *tile, int index = -1);
    void insertTile(const TTileList &tileList, const QList<int> &indexList = QList<int>());
    int removeTile(int index);
    int removeTile(TTile *tile);
    QList<int> removeTile(const QList<int> &indexList);
    QList<int> removeTile(const TTileList &tileList);

    TTile *createTile(TTileId *tileId, const QPointF &pos = QPointF());

signals:
    void tileInserted(const TTileList &tileList, const QList<int> &indexList);
    void tileRemoved(const TTileList &tileList, const QList<int> &indexList);

private:
    LayerType mLayerType;
    TDocument *mDocument;
    TTileList mTileList;

    // IO interface
public:
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

    // TBaseModel interface
public:
    void insertObjects(const TObjectList &objectList, const QList<int> &indexList);
    QList<int> removeObjects(const TObjectList &objectList);
};


#endif // TTILELAYERMODEL_H
