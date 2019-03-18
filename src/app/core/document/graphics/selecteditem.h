#ifndef TSELECTEDITEM_H
#define TSELECTEDITEM_H

#include <QGraphicsObject>
#include "objectitem.h"

class TSelectedItem : public QGraphicsObject
{
public:
    TSelectedItem(QGraphicsItem *parent = nullptr);

    void setObjectItem(TObjectItem *objectItem);

    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *,
               QWidget *) override;

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    QRectF mBoundingRect;
    TObjectItem *mObjectItem;

    // Marching ants effect
    int mUpdateTimer;
    int mOffset = 0;
};
#endif // TSELECTEDITEM_H
