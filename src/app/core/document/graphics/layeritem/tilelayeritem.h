#ifndef TILELAYERITEM_H
#define TILELAYERITEM_H

#include <QList>
#include "layeritem.h"
#include "objectitem/tileitem.h"
#include "objectitem/animationitem.h"
#include "../../model/tilelayermodel.h"

class TTileLayerItem : public TLayerItem
{
    Q_OBJECT

public:
    explicit TTileLayerItem(TTileModel *model, QGraphicsItem *parent = Q_NULLPTR);
    ~TTileLayerItem();

    bool replace(TAnimationItem *animationItem);
    void step();

    TAnimationItem *createAnimationItem(TAnimation *animation);

private slots:
    void slotTileInserted(const TTileList &tileList, const QList<int> &indexList);
    void slotTileRemoved(const TTileList &tileList, const QList<int> &indexList);
    void slotOnTileItemBoundingRectChanged(const QRectF &newRect);

private:
    TTileItemList mTileItemList;
    TTileModel *mTileLayerModel;
    QMap<TTile*, TTileItem*> mTileItemMap;

    void create();
    TTileItem *addTile(TTile *tile);
    void setTileItemTarget(TTileItem *tileItem);

    // TLayerItem interface
public:
    QRectF calcBoundingRect() Q_DECL_OVERRIDE;
    QMap<TTile *, TTileItem *> getTileItemMap() const;
};

typedef QList<TTileLayerItem*> TTileLayerItemList;
#endif // TILELAYERITEM_H
