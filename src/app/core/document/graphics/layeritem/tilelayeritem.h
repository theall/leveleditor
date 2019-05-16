#ifndef TILELAYERITEM_H
#define TILELAYERITEM_H

#include <QList>
#include "layeritem.h"
#include "objectitem/tileitem.h"
#include "../../model/tilelayermodel.h"

class TTileLayerItem : public TLayerItem
{
    Q_OBJECT

public:
    explicit TTileLayerItem(TTileLayerModel *model, QGraphicsItem *parent = Q_NULLPTR);
    ~TTileLayerItem();

private slots:
    void slotTileInserted(const TTileList &tileList, const QList<int> &indexList);
    void slotTileRemoved(const TTileList &tileList, const QList<int> &indexList);

private:
    TLayer *mLayer;
    QRectF mBoundingRect;
    TTileItemList mTileItemList;
    QMap<TTile*, TTileItem*> mTileItemMap;

    void create();
    TTileItem *addTile(TTile *tile);
    void setTileItemTarget(TTileItem *tileItem);

    // TLayerItem interface
public:
    QRectF calcBoundingRect() Q_DECL_OVERRIDE;
};

typedef QList<TTileLayerItem*> TTileLayerItemList;
#endif // TILELAYERITEM_H
