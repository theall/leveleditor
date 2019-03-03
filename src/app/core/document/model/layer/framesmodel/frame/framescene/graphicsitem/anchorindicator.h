#ifndef ANCHORINDICATOR_H
#define ANCHORINDICATOR_H

#include <QGraphicsObject>

/**
 * Pixmap anchor.
 */
class TAnchorIndicator : public QGraphicsObject
{
    Q_OBJECT

public:
    TAnchorIndicator(QGraphicsItem *parent = nullptr);
    ~TAnchorIndicator();

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) Q_DECL_OVERRIDE;

signals:
    void itemMoved(const QPointF &newPos);

    // QGraphicsItem interface
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;
};

#endif // ANCHORINDICATOR_H
