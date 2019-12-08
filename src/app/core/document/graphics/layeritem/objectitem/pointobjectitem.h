#ifndef TPOINTOBJECTITEM_H
#define TPOINTOBJECTITEM_H

#include "objectitem.h"
#include "../../../model/entity/pointobject.h"

class TPointObjectItem : public TObjectItem
{
public:
    TPointObjectItem(TPointObject *pointRect, QGraphicsItem *parent = Q_NULLPTR);
};

#endif // TPOINTOBJECTITEM_H
