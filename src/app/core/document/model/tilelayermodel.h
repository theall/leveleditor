#ifndef TTILELAYERMODEL_H
#define TTILELAYERMODEL_H

#include "basemodel.h"
#include "objectgeneric.hpp"
#include "entity/tile.h"

class TTileModel : public TBaseModel
{
    Q_OBJECT

public:
    enum LayerType {
        Background,
        Foreground
    };
    TTileModel(QObject *parent = nullptr);
    ~TTileModel();

    LayerType layerType() const;
    void setLayerType(const LayerType &layerType);

    TTileList tileList() const;
    int tileSize() const;

    TTile *createTile(TTileId *tileId, const QPointF &pos = QPointF());
    TTile *getTile(int index) const;

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

public:
    DECL_GENERIC_FUNCTIONS(Tile);

signals:
    DECL_GENERIC_SIGNALS(Tile);
};


#endif // TTILELAYERMODEL_H
