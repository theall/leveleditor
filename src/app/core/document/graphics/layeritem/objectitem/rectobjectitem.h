#ifndef TRECTOBJECTITEM_H
#define TRECTOBJECTITEM_H

#include "objectitem.h"
#include "../../../model/entity/rectobject.h"

class TRectObjectItem : public TObjectItem
{
public:
    TRectObjectItem(TRectObject *rectObject, QGraphicsItem *parent = Q_NULLPTR);
};

#endif // TRECTOBJECTITEM_H
