#include "arealayeritem.h"
#include "../../model/areamodel.h"

TAreasLayerItem::TAreasLayerItem(TAreaModel *areasModel, QGraphicsItem *parent) :
    TObjectLayerItem(areasModel, parent)
{
    Q_ASSERT(areasModel);
    connect(areasModel, SIGNAL(objectInserted(TAreaList,QList<int>)), this, SLOT(slotAreaInserted(TAreaList,QList<int>)));
    connect(areasModel, SIGNAL(objectRemoved(TAreaList,QList<int>)), this, SLOT(slotAreaRemoved(TAreaList,QList<int>)));

    for(TArea *area : areasModel->areaList()) {
        addArea(area);
    }

    calcBoundingRect();
}

TAreasLayerItem::~TAreasLayerItem()
{

}

void TAreasLayerItem::slotAreaInserted(const TAreaList &areaList, const QList<int> &)
{
    for(TArea *area : areaList)
        addArea(area);
    calcBoundingRect();
}

void TAreasLayerItem::slotAreaRemoved(const TAreaList &areaList, const QList<int> &)
{
    for(TArea *area : areaList) {
        TAreaItem *areaItem = mAreaItemMap[area];
        if(areaItem) {
            delete areaItem;
            mAreaItemList.removeAll(areaItem);
        }
        mAreaItemMap.remove(area);
    }
    calcBoundingRect();
}

TAreaItem *TAreasLayerItem::addArea(TArea *area)
{
    TAreaItem *areaItem = new TAreaItem(area, this);
    mAreaItemList.append(areaItem);
    mAreaItemMap.insert(area, areaItem);
    return areaItem;
}
