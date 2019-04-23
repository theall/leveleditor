#ifndef TMAINLAYERITEM_H
#define TMAINLAYERITEM_H

#include "layeritem.h"
#include "objectitem/objectitem.h"

class TSceneModel;
class TMainLayerItem : public TLayerItem
{
public:
    explicit TMainLayerItem(TSceneModel *sceneModel, QGraphicsItem *parent = Q_NULLPTR);
    ~TMainLayerItem();

private:
    TSceneModel *mSceneModel;
    TObjectItemList mObjectItemList;

    // TLayerItem interface
public:
    QRectF calcBoundingRect() Q_DECL_OVERRIDE;
};

#endif // TMAINLAYERITEM_H
