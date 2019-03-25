#ifndef TTILEITEM_H
#define TTILEITEM_H

#include <QList>
#include "objectitem.h"
#include "../model/entity/tile.h"

class TTileItem;
class TTrackItem;
class TDoorItem;
class TStartPointItem : public TObjectItem
{
public:
    TStartPointItem(TDoorItem *doorItem);
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

class TRandomRegionItem : public TObjectItem
{
public:
    TRandomRegionItem(TDoorItem *doorItem);

private:
    QRectF mBoundingRect;
};

class TDoorItem : public TObjectItem
{
public:
    TDoorItem(TTileItem *tileItem);
    ~TDoorItem();

    TStartPoint *startPoint() const;

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
    TStartPointItem *mStartPointItem;
    TTrackItem *mDoorStartPointTrackItem;
    TTrackItem *mFollowTileTrackItem;

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
    TTrackItem(TObjectItem *parent, TObjectItem *child);
    ~TTrackItem();

private:
    TObjectItem *mHostObjectItem;
    TObjectItem *mChildObjectItem;
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
    TDoor *door() const;

    TTileItem *targetTileItem() const;
    void setTargetTileItem(TTileItem *targetTileItem);

private:
    TTile *mTile;
    QRectF mBoundingRect;
    TDoorItem *mDoorItem;
    TTrackItem *mTileDoorTrackItem;
    TTileItem *mTargetTileItem;

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
