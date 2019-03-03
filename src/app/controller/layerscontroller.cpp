#include "layerscontroller.h"

TLayersController::TLayersController(QObject *parent) :
    TAbstractController(parent)
{

}

TLayersController::~TLayersController()
{

}

bool TLayersController::joint(TMainWindow *mainWindow, TCore *core)
{
    Q_ASSERT(mainWindow);
    Q_ASSERT(core);

    return TAbstractController::joint(mainWindow, core);
}

void TLayersController::setCurrentDocument(TDocument *document)
{
//    if (mDocument == mapDocument)
//        return;

//    if (mDocument)
//        mDocument->disconnect(this);

//    mDocument = mapDocument;

//    if (mDocument) {
//        connect(mDocument, &MapDocument::currentLayerIndexChanged,
//                this, &TLayerController::updateOpacitySlider);
//        connect(mDocument, &MapDocument::layerChanged,
//                this, &TLayerController::layerChanged);
//        connect(mDocument, &MapDocument::editLayerNameRequested,
//                this, &TLayerController::editLayerName);
//    }

//    mLayerView->setMapDocument(mapDocument);

    //updateOpacitySlider();
}

void TLayersController::slotTimerEvent()
{

}

//void TLayersController::updateOpacitySlider()
//{
//    const bool enabled = mDocument &&
//                         mDocument->currentLayerIndex() != -1;

//    mOpacitySlider->setEnabled(enabled);
//    mOpacityLabel->setEnabled(enabled);

//    mUpdatingSlider = true;
//    if (enabled) {
//        qreal opacity = mDocument->currentLayer()->opacity();
//        mOpacitySlider->setValue((int) (opacity * 100));
//    } else {
//        mOpacitySlider->setValue(100);
//    }
//    mUpdatingSlider = false;
//}


//void TLayersController::layerChanged(int index)
//{
//    if (index != mDocument->currentLayerIndex())
//        return;

//    // Don't update the slider when we're the ones changing the layer opacity
//    if (mChangingLayerOpacity)
//        return;

//    updateOpacitySlider();
//}

//void TLayersController::editLayerName()
//{
//    if (!isVisible())
//        return;

//    const LayerModel *layerModel = mDocument->layersModel();
//    const int currentLayerIndex = mDocument->currentLayerIndex();
//    const int row = layerModel->layerIndexToRow(currentLayerIndex);

//    raise();
//    mLayerView->edit(layerModel->index(row));
//}

//void TLayersController::slotSliderValueChanged(int opacity)
//{
//    if (!mDocument)
//        return;

//    // When the slider changes value just because we're updating it, it
//    // shouldn't try to set the layer opacity.
//    if (mUpdatingSlider)
//        return;

//    const int layerIndex = mDocument->currentLayerIndex();
//    if (layerIndex == -1)
//        return;

//    const Layer *layer = mDocument->map()->layerAt(layerIndex);

//    if ((int) (layer->opacity() * 100) != opacity) {
//        mChangingLayerOpacity = true;
//        LayerModel *layerModel = mDocument->layersModel();
//        const int row = layerModel->layerIndexToRow(layerIndex);
//        layerModel->setData(layerModel->index(row),
//                            qreal(opacity) / 100,
//                            LayerModel::OpacityRole);
//        mChangingLayerOpacity = false;
//    }
//}
