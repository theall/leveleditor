#include "triggerlayeritem.h"
#include "../../model/triggermodel.h"

TTriggerLayerItem::TTriggerLayerItem(TTriggerModel *triggerModel, QGraphicsItem *parent) :
    TLayerItem(triggerModel, parent)
{
    Q_ASSERT(triggerModel);
    for(TTrigger *trigger : triggerModel->triggerList()) {
        TTriggerItem *triggerItem = new TTriggerItem(trigger, this);
        mTriggerItemList.append(triggerItem);
    }
    calcBoundingRect();
}

TTriggerLayerItem::~TTriggerLayerItem()
{

}

QRectF TTriggerLayerItem::calcBoundingRect()
{
    QRectF newRect;
    for(TTriggerItem *triggerItem : mTriggerItemList) {
        newRect = newRect.united(triggerItem->boundingRect());
    }
    setBoundingRect(newRect);
    return newRect;
}
