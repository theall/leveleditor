#ifndef TTILEITEM_H
#define TTILEITEM_H

#include <QList>
#include "objectitem.h"
#include "../model/entity/tile.h"

class TDoorItem : public TObjectItem
{
public:
    TDoorItem(TTile *tile, QGraphicsItem *parent = Q_NULLPTR);

private:
    TTile *mTile;
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

class TTrackItem : public TObjectItem
{
    Q_OBJECT

public:
    TTrackItem(TTile *tile, QGraphicsItem *parent = Q_NULLPTR);
    ~TTrackItem();

private:
    TTile *mTile;
    QPointF mVector;
    QRectF mBoundingRect;

    // QGraphicsItem interface
public:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    // TObjectItem interface
public:
    void propertyValueChanged(PropertyID pid) Q_DECL_OVERRIDE;
};

class TTileItem : public TObjectItem
{
    Q_OBJECT

public:
    TTileItem(TTile *tile, QGraphicsItem *parent = Q_NULLPTR);
    ~TTileItem();

private:
    TTile *mTile;
    QRectF mBoundingRect;
    TDoorItem *mDoorItem;

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
