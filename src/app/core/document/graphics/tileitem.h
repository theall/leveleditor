#ifndef TTILEITEM_H
#define TTILEITEM_H

#include <QList>
#include "objectitem.h"
#include "../model/entity/tile.h"

class TTileItem;
class TStartPointItem : public TObjectItem
{
public:
    TStartPointItem(TTileItem *tileItem);
    ~TStartPointItem();

private:
    TStartPoint *mStartPoint;
    QRectF mBoundingRect;

    void updateBoundingRect();

    // QGraphicsItem interface
public:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    // TObjectItem interface
public:
    void propertyValueChanged(PropertyID pid) Q_DECL_OVERRIDE;
};

class TDoorItem : public TObjectItem
{
public:
    TDoorItem(TTileItem *tileItem);

private:
    enum MouseRegion
    {
        LEFT,
        RIGHT,
        BLANK,
        OUT
    };

    TDoor *mDoor;
    MouseRegion mMouseRegion;
    bool mLeftButtonDown;
    bool mResizeHovered;
    bool mIsVertical;
    QPointF mLeftButtonDownPos;
    QPointF mMovingPos;
    QRectF mMovingRect;
    QRectF mBoundingRect;
    QRectF mRealRect;

    void updateBoundingRect();
    MouseRegion checkMouseRegion(const QPointF &pos);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    // TObjectItem interface
public:
    void propertyValueChanged(PropertyID pid) Q_DECL_OVERRIDE;

    // QGraphicsItem interface
protected:
    void mousePressed(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoved(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleased(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
};

class TTrackItem : public QGraphicsItem
{
public:
    TTrackItem(TTileItem *tileItem, TDoorItem *doorItem);
    ~TTrackItem();

private:
    TTileItem *mTileItem;
    TDoorItem *mDoorItem;
    QRectF mBoundingRect;

    // QGraphicsItem interface
public:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
};

class TTileItem : public TObjectItem
{
    Q_OBJECT

public:
    TTileItem(TTile *tile, QGraphicsItem *parent = Q_NULLPTR);
    ~TTileItem();

    TTile *tile() const;
    TStartPoint *startPoint() const;
    TDoor *door() const;

private:
    TTile *mTile;
    QRectF mBoundingRect;
    TDoorItem *mDoorItem;
    TTrackItem *mTrackItem;
    TStartPointItem *mStartPointItem;

    // QGraphicsItem interface
public:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;

    // TObjectItem interface
public:
    void propertyValueChanged(PropertyID pid) Q_DECL_OVERRIDE;
};

typedef QList<TTileItem*> TTileItemList;
#endif // TTILEITEM_H
