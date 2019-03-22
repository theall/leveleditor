#include "selectionrectangle.h"

#include <QPainter>
#include <QPalette>

TSelectionRectangle::TSelectionRectangle(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{

}

void TSelectionRectangle::setRectangle(const QRectF &rectangle)
{
    prepareGeometryChange();
    mRectangle = rectangle;
}

QRectF TSelectionRectangle::boundingRect() const
{
    return mRectangle.adjusted(-1, -1, 2, 2);
}

void TSelectionRectangle::paint(QPainter *painter,
                               const QStyleOptionGraphicsItem *,
                               QWidget *)
{
    if (mRectangle.isNull())
        return;

    // Draw a rectangle
    QColor green(Qt::green);
    green.setAlpha(128);
    QPen pen(green, 2, Qt::DotLine);
    pen.setCosmetic(true);
    painter->setPen(pen);
    painter->drawRect(mRectangle);
}
