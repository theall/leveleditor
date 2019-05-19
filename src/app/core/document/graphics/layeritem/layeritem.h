#ifndef TLAYERITEM_H
#define TLAYERITEM_H

#include <QGraphicsObject>

class TObject;
class TBaseModel;
class TObjectItem;
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

    virtual QRectF calcBoundingRect() = 0;

private:
    bool mLocked;
    LayerType mLayerType;

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
