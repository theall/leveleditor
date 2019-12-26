#ifndef TLAYERITEM_H
#define TLAYERITEM_H

#include <QGraphicsObject>

#include "objectitem/objectitem.h"

class TObject;
class TBaseModel;
class TLayerItem : public QGraphicsObject
{
    Q_OBJECT

public:
    enum LayerType {
        TILE,
        OBJECT
    };

    TLayerItem(TBaseModel *baseModel, QGraphicsItem *parent = Q_NULLPTR);
    ~TLayerItem();

    TBaseModel *baseModel() const;
    bool locked() const;

    bool isTileLayer() const;
    bool isObjectLayer() const;

    LayerType layerType() const;
    void setLayerType(const LayerType &layerType);

    bool hasItem(TObjectItem *objectItem) const;
    bool hasItem(QGraphicsItem *objectItem) const;

    TObjectItemList getObjectItemList() const;

    virtual QRectF calcBoundingRect();

    void setBoundingRect(const QRectF &rect);

    virtual void step();

    void promote(qreal zIndex);
    void restore();

    bool isFactoryLayer() const;

signals:
    void boundingRectChanged(const QRectF &rect);

private:
    bool mLocked;
    LayerType mLayerType;
    int mSavedZIndex;

private slots:
    void slotLayerVisibilityChanged(bool visible);
    void slotLayerLockChanged(bool locked);

protected:
    QRectF mBoundingRect;
    TBaseModel *mBaseModel;

    // QGraphicsItem interface
public:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
};
typedef QList<TLayerItem*> TLayerItemList;
#endif // TLAYERITEM_H
