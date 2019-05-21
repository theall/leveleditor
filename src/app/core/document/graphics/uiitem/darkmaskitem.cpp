#include "darkmaskitem.h"

#include <QPen>
#include <QBrush>

TDarkMaskItem::TDarkMaskItem(QGraphicsItem *parent) :
    QGraphicsRectItem(parent)
{
    setOpacity(0.6);
    setPen(Qt::NoPen);
    setBrush(Qt::black);
    setRect(QRectF(INT_MIN/512, INT_MIN/512, INT_MAX/256, INT_MAX/256));
}

TDarkMaskItem::~TDarkMaskItem()
{

}
