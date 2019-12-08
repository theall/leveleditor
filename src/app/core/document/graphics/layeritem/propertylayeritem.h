#ifndef TPROPERTYLAYERITEM_H
#define TPROPERTYLAYERITEM_H

#include "layeritem.h"

class TSceneModel;
class TFlagItem;
class TCameraItem;
class TPropertyLayerItem : public TLayerItem
{
    Q_OBJECT

public:
    TPropertyLayerItem(TSceneModel *sceneModel, QGraphicsItem *parent = Q_NULLPTR);
    ~TPropertyLayerItem();

private:
    TCameraItem *mCameraItem;
    TFlagItem *mFlagItem1;
    TFlagItem *mFlagItem2;

private slots:
    void slotlPropertyItemValueChanged(TPropertyItem *item, const QVariant &oldValue);
};

#endif // TPROPERTYLAYERITEM_H
