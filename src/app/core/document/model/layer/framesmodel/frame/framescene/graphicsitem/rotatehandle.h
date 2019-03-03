#ifndef ROTATEHANDLE_H
#define ROTATEHANDLE_H

#include "handle.h"

/**
 * Corner rotation handle.
 */
class TRotateHandle : public THandle
{
public:
    TRotateHandle(AnchorPosition corner, QGraphicsItem *parent = nullptr);
    ~TRotateHandle();

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) Q_DECL_OVERRIDE;

private:
    QPainterPath mArrowPath;

    // THandle interface
public:
    void mouseDragged(const QPointF &distance) Q_DECL_OVERRIDE;

    // QGraphicsItem interface
public:
    int type() const Q_DECL_OVERRIDE;
};

class QGraphicsScene;
class TRotateHandlesManager
{
public:
    TRotateHandlesManager(QGraphicsScene *scene);
    ~TRotateHandlesManager();

    QGraphicsItem *parentItem() const;
    void setParentItem(QGraphicsItem *parentItem);

private:
    QGraphicsItem *mParentItem;
    TRotateHandle *mRotateHandles[CornerAnchorCount];
};

#endif // ROTATEHANDLE_H
