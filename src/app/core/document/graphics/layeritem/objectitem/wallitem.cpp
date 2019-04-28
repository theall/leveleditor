#include "wallitem.h"

TWallItem::TWallItem(TWall *wall, QGraphicsItem *parent) :
    TObjectItem(wall, parent)
  , mWall(wall)
{
    Q_ASSERT(mWall);
    setBorderColor(Qt::yellow);
}

TWallItem::~TWallItem()
{

}

TWall *TWallItem::wall() const
{
    return mWall;
}

void TWallItem::propertyValueChanged(PropertyID)
{

}
