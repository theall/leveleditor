#ifndef RESIZEHANDLE_H
#define RESIZEHANDLE_H

#include "handle.h"

/**
 * A resize handle that allows resizing of areas.
 */
class TResizeHandle : public THandle
{
    Q_OBJECT

public:
    TResizeHandle(AnchorPosition anchorPosition, QGraphicsItem *parent = nullptr);
    ~TResizeHandle();

    AnchorPosition anchorPosition() const;

    void setResizingOrigin(const QPointF &resizingOrigin);
    void setPosResizingOrigin(const QPointF &pos, const QPointF &resizingOrigin);
    QPointF resizingOrigin() const;

    bool resizingLimitHorizontal() const;
    bool resizingLimitVertical() const;

    QRectF boundingRect() const Q_DECL_OVERRIDE;

    void setUseArrow(bool useArrow);

private slots:
    void slotParentAreaChanged(const QRectF &rect);

private:
    AnchorPosition mAnchorPosition;
    QPointF mResizingOrigin;
    bool mResizingLimitHorizontal;
    bool mResizingLimitVertical;
    bool mUseArrow;
    QRectF mParentLastRect;
    QPainterPath mArrowPath;

    // QGraphicsItem interface
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) Q_DECL_OVERRIDE;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

    // THandle interface
public:
    void mouseDragged(const QPointF &distance) Q_DECL_OVERRIDE;

    // QGraphicsItem interface
public:
    int type() const Q_DECL_OVERRIDE;
};

class QGraphicsScene;
class TResizeHandlesManager
{
public:
    TResizeHandlesManager(QGraphicsScene *scene);
    ~TResizeHandlesManager();

    QGraphicsItem *parentItem() const;
    void setParentItem(QGraphicsItem *parentItem);

private:
    QGraphicsItem *mParentItem;
    TResizeHandle *mResizeHandles[AnchorCount];
};

#endif // RESIZEHANDLE_H
