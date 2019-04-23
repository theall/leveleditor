#ifndef TDOORITEM_H
#define TDOORITEM_H

#include "../objectitem.h"

class TStartPoint;
class TDoor;
class TTileItem;
class TStartPointItem;
class TTrackItem;
class TRandomRegionItem;
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
    QRectF mRealRect;
    TStartPointItem *mStartPointItem;
    TTrackItem *mDoorStartPointTrackItem;
    TTrackItem *mFollowTileTrackItem;
    TRandomRegionItem *mRandomRegionItem;
    TTileItem *mFollowTileItem;

    void updateBoundingRect();
    MouseRegion checkMouseRegion(const QPointF &pos);

    // QGraphicsItem interface
public:
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

#endif // TDOORITEM_H
