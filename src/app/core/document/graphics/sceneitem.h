#ifndef TSCENEITEM_H
#define TSCENEITEM_H

#include <QGraphicsObject>

#include "layeritem.h"
#include "hovereditem.h"
#include "../model/scenemodel.h"

class TSceneItem : QGraphicsObject
{
    Q_OBJECT

public:
    explicit TSceneItem(TSceneModel *sceneModel, QGraphicsItem *parent = Q_NULLPTR);
    ~TSceneItem();

private:
    QRectF mBoundingRect;
    bool mIsHovered = false;
    TSceneModel *mSceneModel;
    QGraphicsRectItem *mDarkRectangle;
    QGraphicsRectItem *mBorderRectangle;
    TLayerItemList mLayerItemList;

    void calcBoundingRect();

    // QGraphicsItem interface
public:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
};

#endif // TSCENEITEM_H
