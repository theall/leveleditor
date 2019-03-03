#ifndef SELECTIONGRAPHICSITEM_H
#define SELECTIONGRAPHICSITEM_H

#include <QGraphicsItem>

/**
 * The rectangle used for indicating the dragged area when selecting items.
 */
class TSelectionGraphicsItem : public QGraphicsItem
{
public:
    TSelectionGraphicsItem(QGraphicsItem *parent = nullptr);

    void setRect(const QRectF &rect);

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) Q_DECL_OVERRIDE;

private:
    QRectF mRect;
};

#endif // SELECTIONGRAPHICSITEM_H
