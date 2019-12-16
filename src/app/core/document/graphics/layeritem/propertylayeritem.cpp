#include "propertylayeritem.h"

#include "objectitem/flagitem.h"
#include "objectitem/cameraitem.h"

#include "../../model/sceneModel.h"

TPropertyLayerItem::TPropertyLayerItem(TSceneModel *sceneModel, QGraphicsItem *parent) :
    TLayerItem(sceneModel, parent)
  , mCameraItem(new TCameraItem(this))
{
    setLayerType(TLayerItem::OBJECT);

    Q_ASSERT(sceneModel);

    TPropertySheet *sceneModelPropertySheet = sceneModel->propertySheet();
    if(!sceneModelPropertySheet)
        throw("Property sheet needed in scene model!");
    connect(sceneModelPropertySheet,
            SIGNAL(propertyItemValueChanged(TPropertyItem*,QVariant)),
            this,
            SLOT(slotlPropertyItemValueChanged(TPropertyItem*,QVariant)));

    QRect cameraRect = sceneModel->getCameraAsRect();
    mCameraItem->setBoundingRect(cameraRect);

    mFlagItem1 = new TFlagItem(sceneModel->getFlagPointObject1(), this);
    mFlagItem2 = new TFlagItem(sceneModel->getFlagPointObject2(), this);

    mFlagItem1->setColor(Qt::green);
    mFlagItem2->setColor(Qt::red);

    if(sceneModel->isAdvMap()) {
        // Adv map has no flags
        mFlagItem1->setVisible(false);
        mFlagItem2->setVisible(false);
    }

    calcBoundingRect();
}

TPropertyLayerItem::~TPropertyLayerItem()
{

}

void TPropertyLayerItem::slotlPropertyItemValueChanged(TPropertyItem *item, const QVariant &)
{
    if(!item)
        return;

    PropertyID pid = item->propertyId();
    if(pid == PID_SCENE_CAMERA) {
        mCameraItem->setBoundingRect(item->value().toRect());
    }
}

QRectF TPropertyLayerItem::calcBoundingRect()
{
    QRectF rect(0, 0, 1, 1);
    rect = rect.united(mFlagItem1->boundingRect());
    rect = rect.united(mFlagItem2->boundingRect());
    return rect;
}
