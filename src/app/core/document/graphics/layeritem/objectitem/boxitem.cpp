#include "boxitem.h"

#include <QPainter>

TBoxItem::TBoxItem(TBox *box, QGraphicsItem *parent) :
    TRectObjectItem(box, parent)
  , mBox(box)
{
    Q_ASSERT(mBox);
    setBorderColor(Qt::magenta);
}

TBoxItem::~TBoxItem()
{

}

TBox *TBoxItem::box() const
{
    return mBox;
}

void TBoxItem::propertyValueChanged(PropertyID)
{

}

void TBoxItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(Qt::white);
    painter->setPen(pen);
    painter->drawLines(mBox->pointList().toVector());

    for(QPoint point : mBox->pointList()) {
        QRectF fillRect(0, 0, 5, 5);
        fillRect.moveCenter(point);
        painter->fillRect(fillRect, Qt::white);
    }
    TRectObjectItem::paint(painter, option, widget);
}
