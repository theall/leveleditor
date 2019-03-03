#include "selectiongraphicsitem.h"

#include <QApplication>
#include <QPainter>
#include <QPalette>

TSelectionGraphicsItem::TSelectionGraphicsItem(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    setZValue(10000);
}

void TSelectionGraphicsItem::setRect(const QRectF &rect)
{
    prepareGeometryChange();
    mRect = rect;
}

QRectF TSelectionGraphicsItem::boundingRect() const
{
    return mRect.adjusted(-1, -1, 2, 2);
}

void TSelectionGraphicsItem::paint(QPainter *painter,
                               const QStyleOptionGraphicsItem *, QWidget *)
{
    if (mRect.isNull())
        return;

    // Draw a shadow
//    QColor black(Qt::black);
//    black.setAlpha(128);
//    QPen pen(black, 2, Qt::DotLine);
//    pen.setCosmetic(true);
//    painter->setPen(pen);
//    painter->drawRect(mRect.translated(1, 1));

    // Draw a rectangle in the gray color
    QColor highlight = Qt::gray;
    highlight.setAlpha(128);
    QPen pen(highlight, 1, Qt::DotLine);
    painter->setPen(pen);
    //painter->setBrush(highlight);
    painter->drawRect(mRect);
}
