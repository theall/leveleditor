#ifndef TSCENEITEM_H
#define TSCENEITEM_H

#include <QGraphicsObject>

#include "../model/scenemodel.h"
#include "layeritem/layeritem.h"
#include "layeritem/tilelayeritem.h"

class TDarkMaskItem;
class TPropertyLayerItem;
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
    QGraphicsRectItem *mBorderRectangle;
    TLayerItemList mLayerItemList;
    TTileLayerItemList mTileLayerItemList;
    QMap<TBaseModel*, TLayerItem*> mModelLayerMap;
    TLayerItem *mCurrentLayerItem;
    TDarkMaskItem *mDarkMaskItem;
    TPropertyLayerItem *mPropertylayerItem;

    void calcBoundingRect();
    void internalAdd(TBaseModel *baseModel, TLayerItem *layerItem);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
};

#endif // TSCENEITEM_H
