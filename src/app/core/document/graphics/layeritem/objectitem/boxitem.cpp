#include "boxitem.h"

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
