#include "objectlayeritem.h"

TObjectLayerItem::TObjectLayerItem(TBaseModel *baseModel, QGraphicsItem *parent) :
    TLayerItem(baseModel, parent)
{
    setLayerType(TLayerItem::OBJECT);
}

TObjectLayerItem::~TObjectLayerItem()
{

}
