#include "dareaitem.h"

TDAreaItem::TDAreaItem(TDArea *darea, QGraphicsItem *parent) :
    TObjectItem(darea, parent)
  , mDArea(darea)
{
    Q_ASSERT(mDArea);
    setBorderColor(Qt::red);
}

TDAreaItem::~TDAreaItem()
{

}

TDArea *TDAreaItem::darea() const
{
    return mDArea;
}

void TDAreaItem::propertyValueChanged(PropertyID)
{

}
