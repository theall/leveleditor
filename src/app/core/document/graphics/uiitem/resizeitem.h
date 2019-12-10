#ifndef TRESIZEITEM_H
#define TRESIZEITEM_H

#include <QGraphicsItem>

enum HandleAnchor
{
    HA_LEFT_TOP,
    HA_TOP_CENTER,
    HA_TOP_RIGHT,
    HA_LEFT_CENTER,
    HA_RIGHT_CENTER,
    HA_LEFT_BOTTOM,
    HA_BOTTOM_CENTER,
    HA_BOTTOM_RIGHT,
    HA_COUNT
};

class THandleItem : public QGraphicsItem
{
public:
    THandleItem(const HandleAnchor &handleAnchor, QGraphicsItem *parent = nullptr);

    HandleAnchor anchor() const;

    void setAnchor(const HandleAnchor &anchor);

    void setPos(float x, float y);
    void setPos(const QPointF &pos);

private:
    HandleAnchor mAnchor;
    QRectF mBoudingRect;
    QPointF mPoint;

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class TResizeItem : public QGraphicsItem
{
public:
    TResizeItem(QGraphicsItem *parent = nullptr);

    void setRect(const QRectF &rect);

private:
    QRectF mBoundingRect;
    THandleItem* mHandleItems[HA_COUNT];

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // TRESIZEITEM_H
