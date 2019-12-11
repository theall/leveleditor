#ifndef TTRIGGERLAYERITEM_H
#define TTRIGGERLAYERITEM_H

#include "layeritem.h"
#include "objectitem/triggeritem.h"

class TTriggerModel;
class TTriggerLayerItem : public TLayerItem
{
public:
    TTriggerLayerItem(TTriggerModel *triggerModel, QGraphicsItem *parent = Q_NULLPTR);
    ~TTriggerLayerItem();

private:
    TTriggerItemList mTriggerItemList;
};

#endif // TTRIGGERLAYERITEM_H
