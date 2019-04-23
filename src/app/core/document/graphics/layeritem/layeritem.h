#ifndef TLAYERITEM_H
#define TLAYERITEM_H

#include <QGraphicsObject>
class TLayerItem : public QGraphicsObject
{
public:
    TLayerItem(QGraphicsItem *parent = Q_NULLPTR);

    virtual QRectF calcBoundingRect() = 0;

protected:
    QRectF mBoundingRect;

    // QGraphicsItem interface
public:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
};
typedef QList<TLayerItem*> TLayerItemList;
#endif // TLAYERITEM_H
