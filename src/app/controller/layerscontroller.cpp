#include "layerscontroller.h"
#include "gui/component/layerdock/layerdock.h"
#include "gui/component/layerdock/layerview.h"

#include "core/document/graphics/layeritem/propertylayeritem.h"

TLayersController::TLayersController(QObject *parent) :
    TAbstractController(parent)
  , mLayerView(nullptr)
  , mLayerDock(nullptr)
{

}

TLayersController::~TLayersController()
{

}

bool TLayersController::joint(TMainWindow *mainWindow, TCore *core)
{
    Q_ASSERT(mainWindow);
    Q_ASSERT(core);

    mLayerDock = mainWindow->getLayerDock();
    connect(mLayerDock, SIGNAL(layerOpacityChanged(QList<int>,float)), this, SLOT(slotLayerOpacityChanged(QList<int>,float)));

    mLayerView = mLayerDock->layerView();
    connect(mLayerView, SIGNAL(currentRowChanged(int)), this, SLOT(slotCurrentLayerSelected(int)));
    connect(mLayerView, SIGNAL(requestShowLayers(QList<int>,bool)), this, SLOT(slotRequestShowLayers(QList<int>,bool)));
    connect(mLayerView, SIGNAL(requestLockLayers(QList<int>,bool)), this, SLOT(slotRequestLockLayers(QList<int>,bool)));

    return TAbstractController::joint(mainWindow, core);
}

void TLayersController::setCurrentDocument(TDocument *document)
{
    if(mDocument == document)
        return;

    if(mDocument)
        mDocument->disconnect(this);

    TSceneModel *model = nullptr;

    if(document)
    {
        model = document->getSceneModel();
    }
    mLayerView->setModel(model);

    if(model) {
        mLayerView->selectRow(model->getCurrentIndex());
    }
    if(!document)
        return;

    TGraphicsScene *scene = document->graphicsScene();
    for(int row : mLayerView->getSelectedRows()){
        TLayerItem *layerItem = scene->getLayerItem(row);
        if(dynamic_cast<TPropertyLayerItem*>(layerItem)) {
            mLayerDock->setOpacitySlider(false);
        } else
            mLayerDock->setOpacitySlider(true);

        if(layerItem) {
            mLayerDock->setOpacitySliderValue(layerItem->opacity());
        }
    }
}

void TLayersController::slotCurrentLayerSelected(int row)
{
    if(!mDocument)
        return;

    mDocument->getSceneModel()->setCurrentIndex(row);
    TSceneModel *sceneModel = getCurrentSceneModel();
    TBaseModel *baseModel = sceneModel->getBaseModel(row);
    mLayerDock->setOpacitySliderValue(baseModel?baseModel->transparency():1.0);
    TGraphicsScene *graphicsScene = mDocument->graphicsScene();
    TLayerItem *layerItem = graphicsScene->getLayerItem(row);
    layerItem->setOpacity(baseModel->transparency());
//    mLayerDock->setOpacitySliderValue(layerItem?layerItem->opacity():1.0);

    // Notify main controller
    emit layerSelected(row);
}

void TLayersController::slotLayerOpacityChanged(const QList<int> &rows, float opacity)
{
    if(!mDocument)
        return;

    TGraphicsScene *scene = mDocument->graphicsScene();
    TSceneModel *sceneModel = getCurrentSceneModel();
    for(int row : rows) {
        TBaseModel *baseModel = sceneModel->getBaseModel(row);
        baseModel->setTransparency(opacity);
    }
    for(int row : rows) {
        TLayerItem *layerItem = scene->getLayerItem(row);
        if(layerItem) {
            layerItem->setOpacity(opacity);
        }
    }
}

void TLayersController::slotRequestShowLayers(const QList<int> &rows, bool show)
{
    TSceneModel *sceneModel = getCurrentSceneModel();
    if(!sceneModel)
        return;

    TBaseModel *baseModel = sceneModel->getCurrentModel();
    mLayerView->setActionShowHideState(baseModel->visible());

    for(int index : rows) {
        TBaseModel *baseModel = sceneModel->getBaseModel(index);
        if(baseModel)
            baseModel->setVisibility(show);
    }
}

void TLayersController::slotRequestLockLayers(const QList<int> &rows, bool lock)
{
    TSceneModel *sceneModel = getCurrentSceneModel();
    if(!sceneModel)
        return;

    TBaseModel *baseModel = sceneModel->getCurrentModel();
    mLayerView->setActionLockUnLockState(baseModel->locked());

    for(int index : rows) {
        TBaseModel *baseModel = sceneModel->getBaseModel(index);
        if(baseModel)
            baseModel->setLocked(lock);
    }
}

void TLayersController::slotTimerEvent()
{

}
