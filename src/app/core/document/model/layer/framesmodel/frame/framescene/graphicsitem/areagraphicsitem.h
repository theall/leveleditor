#ifndef AREAGRAPHICSITEM_H
#define AREAGRAPHICSITEM_H

#include "../../area.h"

/**
 * A graphics item displaying an area.
 */
class TAreaGraphicsItem : public QGraphicsObject
{
    Q_OBJECT

public:
    TAreaGraphicsItem(TArea *area, QGraphicsItem *parent = nullptr);
    ~TAreaGraphicsItem();

    // QGraphicsItem
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) Q_DECL_OVERRIDE;

    /**
     * Resizes the associated area.
     */
    void resize(const QSizeF &size);

    /**
     * Sets a new polygon on the associated object.
     */
    void setPolygon(const QPolygonF &polygon);

    TArea *area() const;

    QColor color() const;

    void setColor(const QColor &color);

    // This function is for changing area's position with undocommand, don't
    // call setPos directly.
    void cmdSetRect(const QRectF &rect);
    TPropertySheet *propertySheet() const;
    TArea::Type areaType() const;

signals:
    void areaChanged(const QRectF &rect);

private slots:
    void slotPropertyChanged(PropertyID id, const QVariant &value);

private:
    TArea *mArea;
    qreal mScale;

    /** Bounding rect cached, for adapting to geometry change correctly. */
    QRectF mBoundingRect;
    QColor mColor;      // Cached color of the area
    QPointF mLastPosition;
    QSizeF mLastSize;
    QPointF mMousePressedPos;
    bool mMousePressed;

    // QGraphicsItem interface
protected:
    int type() const Q_DECL_OVERRIDE;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
};

#endif // AREAGRAPHICSITEM_H
