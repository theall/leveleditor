#ifndef TAREALAYERITEM_H
#define TAREALAYERITEM_H

#include "objectlayeritem.h"
#include "objectitem/areaitem.h"

class TAreasModel;
class TAreasLayerItem : public TObjectLayerItem
{
    Q_OBJECT

public:
    explicit TAreasLayerItem(TAreasModel *areasModel, QGraphicsItem *parent = Q_NULLPTR);
    ~TAreasLayerItem();

private slots:
    void slotAreaInserted(const TAreaList &areaList, const QList<int> &indexList);
    void slotAreaRemoved(const TAreaList &areaList, const QList<int> &indexList);

private:
    TAreasModel *mAreasModel;
    TAreaItemList mAreaItemList;
    QMap<TArea*, TAreaItem*> mAreaItemMap;

    TAreaItem *addArea(TArea *area);
};

#endif // TAREALAYERITEM_H
