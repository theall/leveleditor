#ifndef TSCENEITEM_H
#define TSCENEITEM_H

#include <QGraphicsObject>

#include "cameraitem.h"
#include "../model/scenemodel.h"
#include "layeritem/layeritem.h"
#include "layeritem/tilelayeritem.h"
#include "uiitem/hovereditem.h"
#include "uiitem/darkmaskitem.h"

class TSceneItem : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit TSceneItem(TSceneModel *sceneModel, QGraphicsItem *parent = Q_NULLPTR);
    ~TSceneItem();

    TLayerItem *getLayerItem(int index) const;
    TLayerItemList getLayerItemList() const;

    TLayerItem *getCurrentLayerItem() const;
    void setCurrentLayerItem(TLayerItem *currentLayerItem);

    void step();

signals:
    void boundingRectChanged(const QRectF &newRect);

private slots:
    void slotOnSceneModelCurrentIndexChanged(int index);
    void slotLayerBoundingRectChanged(const QRectF &rect);
    void slotSceneModelPropertyItemValueChanged(TPropertyItem *item, const QVariant &oldValue);

private:
    QRectF mBoundingRect;
    bool mIsHovered;
    TSceneModel *mSceneModel;
    TCameraItem *mCameraItem;
    QGraphicsRectItem *mBorderRectangle;
    TLayerItemList mLayerItemList;
    TTileLayerItemList mTileLayerItemList;
    QMap<TBaseModel*, TLayerItem*> mModelLayerMap;
    TLayerItem *mCurrentLayerItem;
    TDarkMaskItem *mDarkMaskItem;
    void calcBoundingRect();

    // QGraphicsItem interface
public:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
};

#endif // TSCENEITEM_H
