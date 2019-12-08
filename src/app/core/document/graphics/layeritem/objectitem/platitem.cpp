#include "platitem.h"

TPlatItem::TPlatItem(TPlat *plat, QGraphicsItem *parent) :
    TRectObjectItem(plat, parent)
  , mPlat(plat)
{
    Q_ASSERT(mPlat);
    setBorderColor(Qt::blue);
}

TPlatItem::~TPlatItem()
{

}

TPlat *TPlatItem::plat() const
{
    return mPlat;
}

void TPlatItem::propertyValueChanged(PropertyID)
{

}
