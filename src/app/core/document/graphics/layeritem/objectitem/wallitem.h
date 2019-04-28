#ifndef TWALLITEM_H
#define TWALLITEM_H

#include "objectitem.h"
#include "../../../model/entity/wall.h"

class TWallItem : public TObjectItem
{
    Q_OBJECT

public:
    explicit TWallItem(TWall *wall, QGraphicsItem *parent = Q_NULLPTR);
    ~TWallItem();

    TWall *wall() const;

private:
    TWall *mWall;

    // TObjectItem interface
public:
    void propertyValueChanged(PropertyID pid) Q_DECL_OVERRIDE;
};
typedef QList<TWallItem*> TWallItemList;

#endif // TWALLITEM_H
