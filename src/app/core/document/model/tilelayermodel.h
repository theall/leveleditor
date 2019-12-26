#ifndef TTILELAYERMODEL_H
#define TTILELAYERMODEL_H

#include "basemodel.h"
#include "objectgeneric.hpp"
#include "entity/tile.h"
#include "genericmodel.h"

#define TILE_DEFAULT_POS_X 5000
#define TILE_DEFAULT_POS_Y 5000

class TTileModel : public TGenericModel<TTile>
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
    int getTileIndex(TTile *tile);

    TTile *createTile(TTileId *tileId, const QPointF &pos = QPointF(TILE_DEFAULT_POS_X,TILE_DEFAULT_POS_Y));
    TTile *getTile(int index) const;

signals:
    void objectInserted(const TTileList &objectList, const QList<int> &indexList);
    void objectRemoved(const TTileList &objectList, const QList<int> &indexList);

private:
    LayerType mLayerType;
    TDocument *mDocument;

    // IO interface
public:
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

protected:
    virtual void onObjectInserted(const TObjectList &objectList, const QList<int> &indexList) Q_DECL_OVERRIDE;
    virtual void onObjectRemoved(const TObjectList &objectList, const QList<int> &indexList) Q_DECL_OVERRIDE;
};


#endif // TTILELAYERMODEL_H
