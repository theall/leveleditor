#ifndef HANDLE_H
#define HANDLE_H

#include <QVariant>
#include <QGraphicsObject>

#include "graphicsitemutil.h"

enum AnchorPosition {
    TopLeftAnchor,
    TopRightAnchor,
    BottomLeftAnchor,
    BottomRightAnchor,

    TopAnchor,
    LeftAnchor,
    RightAnchor,
    BottomAnchor,

    CornerAnchorCount = 4,
    AnchorCount = 8,
};

/**
 * Shared superclass for rotation and resizing handles.
 */
class THandle : public QGraphicsObject
{
public:
    THandle(QGraphicsItem *parent = nullptr, bool visibility = false);
    ~THandle();

    virtual void mouseDragged(const QPointF &distance) = 0;

protected:
    bool mUnderMouse;
    bool mMousePressed;
    QPointF mMousePressedPos;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *) Q_DECL_OVERRIDE;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *) Q_DECL_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
};


#endif // HANDLE_H
