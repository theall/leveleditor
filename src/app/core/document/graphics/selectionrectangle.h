#pragma once

#include <QGraphicsItem>

/**
 * The rectangle used for indicating the dragged area when selecting items.
 */
class TSelectionRectangle : public QGraphicsItem
{
public:
    TSelectionRectangle(QGraphicsItem *parent = nullptr);

    void setRectangle(const QRectF &rectangle);

    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

private:
    QRectF mRectangle;
};

