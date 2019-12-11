#ifndef TRESIZEITEM_H
#define TRESIZEITEM_H

#include <QGraphicsObject>

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

class THandleItem : public QGraphicsObject
{
    Q_OBJECT

public:
    THandleItem(const HandleAnchor &handleAnchor, QGraphicsItem *parent = nullptr);

    HandleAnchor anchor() const;

    void setAnchor(const HandleAnchor &anchor);

    void setPos(float x, float y, bool emitSignal = true);
    void setPos(const QPointF &pos, bool emitSignal = true);

    void move(const QPointF &offset, bool emitSignal = true);

signals:
    void moved(const QPointF &offset);

private:
    QPointF mPoint;
    HandleAnchor mAnchor;
    QRectF mPaintingRect;
    QRectF mBoundingRect;

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class TResizeItem : public QGraphicsObject
{
    Q_OBJECT

public:
    TResizeItem(QGraphicsItem *parent = nullptr);

    void setRect(const QRectF &rect);

    THandleItem *currentHandleItem() const;
    void setCurrentHandleItem(THandleItem *currentHandleItem);

    bool startResizing();
    void endResizing();

private:
    QRectF mBoundingRect;
    THandleItem *mCurrentHandleItem;
    THandleItem *mHandleItems[HA_COUNT];

signals:
    void requestAdjustRect(const QMarginsF &margins);

private slots:
    void slotHandleMoved(const QPointF &offset);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // TRESIZEITEM_H
