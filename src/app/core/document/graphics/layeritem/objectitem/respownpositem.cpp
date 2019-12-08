#include "respownpositem.h"
#include "../../../model/entity/respawn.h"

#include <QPen>
#include <QPainter>

TRespownPosItem::TRespownPosItem(TRespawn *respawn, QGraphicsItem *parent) :
    TPlayerItem(respawn->respownPointObject(), parent)
  , mRespawn(respawn)
{
    setColor(Qt::blue);
}

TRespownPosItem::~TRespownPosItem()
{

}

void TRespownPosItem::propertyValueChanged(PropertyID)
{

}
