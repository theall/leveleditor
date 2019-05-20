#ifndef TOBJECTAREAITEM_H
#define TOBJECTAREAITEM_H

#include <QGraphicsItem>

/**
 * Present a object area before it's been added
 */
class TObjectAreaItem : public QGraphicsItem
{
public:
    explicit TObjectAreaItem(QGraphicsItem *parent = nullptr);
    ~TObjectAreaItem();

    void setRectangle(const QRectF &rectangle);
    void setColor(const QColor &color);

private:
    QColor mColor;
    QRectF mRectangle;

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // TOBJECTAREAITEM_H
