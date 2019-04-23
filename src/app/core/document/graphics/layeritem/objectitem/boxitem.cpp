#include "boxitem.h"
#include <QPainter>

TBoxItem::TBoxItem(TBox *box, QGraphicsItem *parent) :
    TObjectItem(box, parent)
  , mBox(box)
  , mColor(Qt::red)
{
    Q_ASSERT(mBox);
}

TBoxItem::~TBoxItem()
{

}

TBox *TBoxItem::box() const
{
    return mBox;
}

void TBoxItem::setBox(TBox *box)
{
    mBox = box;
}

QColor TBoxItem::color() const
{
    return mColor;
}

void TBoxItem::setColor(const QColor &color)
{
    mColor = color;
}

QRectF TBoxItem::boundingRect() const
{
    return mBox->rect();
}

void TBoxItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPen pen(mColor);
    painter->setPen(pen);
    painter->drawRect(mBox->rect());
}

QPainterPath TBoxItem::shape() const
{
    QPainterPath p;
    p.addRect(mBox->rect());
    return p;
}

void TBoxItem::propertyValueChanged(PropertyID pid)
{
    // Notify to selection item or hovering item
    if(pid==PID_AREA_RECT) {
        emit boundingRectChanged();
    }
}
