#include "areaitem.h"
#include <QPainter>

TAreaItem::TAreaItem(TArea *area, QGraphicsItem *parent) :
    TObjectItem(area, parent)
  , mArea(area)
{
    Q_ASSERT(mArea);
    setBorderColor(Qt::green);
}

TAreaItem::~TAreaItem()
{

}

TArea *TAreaItem::area() const
{
    return mArea;
}

void TAreaItem::propertyValueChanged(PropertyID)
{

}
