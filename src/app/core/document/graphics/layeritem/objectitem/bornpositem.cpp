#include "bornpositem.h"

#include "../../../model/entity/respawn.h"

#include <QPen>
#include <QPainter>

TBornPosItem::TBornPosItem(TRespawn *respawn,QGraphicsItem *parent) :
    TPlayerItem(respawn->startPointObject(), parent)
  , mRespawn(respawn)
{
    setColor(Qt::red);
}

TBornPosItem::~TBornPosItem()
{

}

void TBornPosItem::propertyValueChanged(PropertyID)
{

}
