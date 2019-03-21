#ifndef TSELECTEDITEM_H
#define TSELECTEDITEM_H

#include <QList>
#include <QGraphicsObject>
#include "objectitem.h"

class TSelectedItem : public QGraphicsObject
{
    Q_OBJECT

public:
    TSelectedItem(QGraphicsItem *parent = nullptr);
    ~TSelectedItem();

    void setObjectItem(TObjectItem *objectItem);

    void step();
    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *,
               QWidget *) override;

private slots:
    void slotObjectBoundingRectChanged();

private:
    int mOffset;
    QRectF mBoundingRect;
    TObjectItem *mObjectItem;
};

typedef QList<TSelectedItem*> TSelectedItemList;
#endif // TSELECTEDITEM_H
