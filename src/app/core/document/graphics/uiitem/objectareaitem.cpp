#include "objectareaitem.h"

#include <QPainter>
#include <QPalette>

TObjectAreaItem::TObjectAreaItem(QGraphicsItem *parent) :
    QGraphicsItem(parent)
  , mColor(Qt::white)
{

}

TObjectAreaItem::~TObjectAreaItem()
{

}

void TObjectAreaItem::setRectangle(const QRectF &rectangle)
{
    prepareGeometryChange();
    mRectangle = rectangle;
}

void TObjectAreaItem::setColor(const QColor &color)
{
    mColor = color;
}

QRectF TObjectAreaItem::boundingRect() const
{
    return mRectangle.adjusted(-1, -1, 2, 2);
}

void TObjectAreaItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (mRectangle.isNull())
        return;

    // Draw a rectangle
    QColor green(mColor);
    green.setAlpha(128);
    QPen pen(green, 2, Qt::SolidLine);
    pen.setCosmetic(true);
    painter->setPen(pen);
    painter->drawRect(mRectangle);
}
