#ifndef TLAYERITEM_H
#define TLAYERITEM_H

#include <QGraphicsObject>

class TBaseModel;
class TLayerItem : public QGraphicsObject
{
    Q_OBJECT

public:
    TLayerItem(TBaseModel *baseModel, QGraphicsItem *parent = Q_NULLPTR);
    ~TLayerItem();

    TBaseModel *baseModel() const;
    bool locked() const;

    virtual QRectF calcBoundingRect() = 0;

private:
    bool mLocked;

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
