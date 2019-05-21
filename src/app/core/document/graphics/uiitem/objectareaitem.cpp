#include "objectareaitem.h"

#include <QPainter>
#include <QPalette>

TObjectAreaItem::TObjectAreaItem(QGraphicsItem *parent) :
    QGraphicsItem(parent)
  , mColor(Qt::green)
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
    return mRectangle;
}

void TObjectAreaItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (mRectangle.isNull())
        return;

    // Draw a rectangle
    QColor color(mColor);
    color.setAlpha(128);
    QPen pen(color, 2, Qt::SolidLine);
    pen.setCosmetic(true);
    painter->setPen(pen);
    painter->drawRect(mRectangle);
}
