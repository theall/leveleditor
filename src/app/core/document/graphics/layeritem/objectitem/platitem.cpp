#include "platitem.h"

TPlatItem::TPlatItem(TPlat *plat, QGraphicsItem *parent) :
    TObjectItem(plat, parent)
  , mPlat(plat)
{
    Q_ASSERT(mPlat);
    setBorderColor(Qt::magenta);
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
