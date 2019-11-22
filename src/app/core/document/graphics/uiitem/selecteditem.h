#ifndef TSELECTEDITEM_H
#define TSELECTEDITEM_H

#include <QList>
#include <QGraphicsObject>
#include "../layeritem/objectitem/objectitem.h"

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

    void move(const QPointF &offset);

private slots:
    void slotObjectBoundingRectChanged(const QRectF &rect);
    void slotOnObjectDestroyed(QObject *object);

private:
    int mOffset;
    QRectF mBoundingRect;
    TObjectItem *mObjectItem;

    void setBoundingRect(const QRectF &rect = QRectF());
};

typedef QList<TSelectedItem*> TSelectedItemList;
#endif // TSELECTEDITEM_H
