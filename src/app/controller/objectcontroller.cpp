#include "objectcontroller.h"

#include "../gui/component/objectdock/objectdock.h"
#include "../gui/component/objectdock/objectcontainer.h"
#include "../gui/component/objectdock/objectlistview.h"
#include "../gui/component/objectdock/subcontrolobjectlistview.h"
#include "../gui/component/tabwidget/graphicsview.h"

#include "core/document/model/basemodel.h"
#include "core/document/model/tilelayermodel.h"
#include "core/document/model/areamodel.h"
#include "core/document/model/boxmodel.h"
#include "core/document/model/dareamodel.h"
#include "core/document/model/platModel.h"
#include "core/document/model/wallModel.h"
#include "core/document/model/respawnmodel.h"
#include "core/document/model/enemyFactoryModel.h"
#include "core/document/model/triggermodel.h"
#include "core/document/model/scenemodel.h"

TObjectController::TObjectController(QObject *parent) :
    TAbstractController(parent)
  , mObjectListView(nullptr)
{

}

TObjectController::~TObjectController()
{

}

bool TObjectController::joint(TMainWindow *mainWindow, TCore *core)
{
    Q_ASSERT(mainWindow);
    Q_ASSERT(core);

    mObjectListView = mainWindow->getObjectDock()->getObjectListView();
    connect(mObjectListView, SIGNAL(indexPressed(const QModelIndex)), this, SLOT(slotObjectIndexPressed(const QModelIndex)));
    mSubControlObjectListView = mainWindow->getObjectDock()->getSubControlObjectListView();
    return TAbstractController::joint(mainWindow, core);
}

void TObjectController::setCurrentDocument(TDocument *document)
{
    Q_UNUSED(document);
    if(!document) {
        return ;
    }
    TGraphicsScene *graphicsScene = document->graphicsScene();
    mSceneModel = document->getSceneModel();
    connect(graphicsScene, SIGNAL(selectedObjectChanged(TObject*,TObject*)), this, SLOT(slotOnSelectedObjectChanged(TObject*,TObject*)));
}

void TObjectController::setObjectListViewModel(TBaseModel *baseModel)
{
    TBaseModel *basemodel = mSceneModel->getCurrentModel();
    if(dynamic_cast<TSceneModel*>(basemodel)) {
        mObjectListView->setModel(nullptr);
        return ;
    }
    mObjectListView->setModel(baseModel);
}

void TObjectController::setSubControlObjectListViewModel(TBaseModel *baseModel){

}

void TObjectController::slotOnSelectedObjectChanged(TObject *, TObject *current)
{
    TBaseModel *baseModel = mSceneModel->getCurrentModel();
    QModelIndex parent = QModelIndex();
    if(TTileModel *tileModel = dynamic_cast<TTileModel*>(baseModel)) {
        mObjectListView->selectRow(tileModel->currentIndex(current), parent);
    } else if(TAreaModel *areaModel = dynamic_cast<TAreaModel*>(baseModel)) {
        mObjectListView->selectRow(areaModel->currentIndex(current), parent);
    } else if(TBoxModel *boxModel = dynamic_cast<TBoxModel*>(baseModel)) {
        mObjectListView->selectRow(boxModel->currentIndex(current), parent);
    } else if(TDAreaModel *dareaModel = dynamic_cast<TDAreaModel*>(baseModel)) {
        mObjectListView->selectRow(dareaModel->currentIndex(current), parent);
    } else if(TPlatModel *platModel = dynamic_cast<TPlatModel*>(baseModel)) {
        mObjectListView->selectRow(platModel->currentIndex(current), parent);
    } else if(TWallModel *wallModel = dynamic_cast<TWallModel*>(baseModel)) {
        mObjectListView->selectRow(wallModel->currentIndex(current), parent);
    } else if(TRespawnModel *respawModel = dynamic_cast<TRespawnModel*>(baseModel)) {
        TRespawn *respawn = (TRespawn*)current->parent();
        int index = respawModel->indexOf(respawn);
        if(index == -1)
            return;

        QModelIndex modelIndex = respawModel->index(index, 0, QModelIndex());
        if(respawn->startPointObject() == current) {
            mObjectListView->selectRow(1, modelIndex);
        } else {
            mObjectListView->selectRow(0, modelIndex);
        }
    } else if(TEnemyFactoryModel *enemyFactoryModel = dynamic_cast<TEnemyFactoryModel*>(baseModel)) {
        mObjectListView->selectRow(enemyFactoryModel->currentIndex(current), parent);
    } else if(TTriggerModel *triggerModel = dynamic_cast<TTriggerModel*>(baseModel)) {
        mObjectListView->selectRow(triggerModel->currentIndex(current), parent);
    }
}

void TObjectController::slotObjectIndexPressed(const QModelIndex &index)
{
    TBaseModel *baseModel = mSceneModel->getCurrentModel();
    int row = index.row();

    if(TTileModel *tileModel = dynamic_cast<TTileModel*>(baseModel)) {
        selectAndCenterOn(tileModel->getObject(row));
    } else if(TAreaModel *areaModel = dynamic_cast<TAreaModel*>(baseModel)) {
        selectAndCenterOn(areaModel->getObject(row));
    } else if(TBoxModel *boxModel = dynamic_cast<TBoxModel*>(baseModel)) {
        selectAndCenterOn(boxModel->getObject(row));
    } else if(TDAreaModel *dareaModel = dynamic_cast<TDAreaModel*>(baseModel)) {
        selectAndCenterOn(dareaModel->getObject(row));
    } else if(TPlatModel *platModel = dynamic_cast<TPlatModel*>(baseModel)) {
        selectAndCenterOn(platModel->getObject(row));
    } else if(TWallModel *wallModel = dynamic_cast<TWallModel*>(baseModel)) {
        selectAndCenterOn(wallModel->getObject(row));
    } else if(dynamic_cast<TRespawnModel*>(baseModel)) {
        selectAndCenterOn(reinterpret_cast<TObject*>(index.internalPointer()));
    } else if(TEnemyFactoryModel *enemyFactoryModel = dynamic_cast<TEnemyFactoryModel*>(baseModel)) {
        selectAndCenterOn(enemyFactoryModel->getObject(row));
    } else if(TTriggerModel *triggerModel = dynamic_cast<TTriggerModel*>(baseModel)) {
        selectAndCenterOn(triggerModel->getObject(row));
    }
}

void TObjectController::slotTimerEvent()
{

}

void TObjectController::selectAndCenterOn(TObject *object)
{
    TObjectItem *objectItem = TObjectItem::getObjectItem(object);
    if(!objectItem)
        return;

    TGraphicsScene *graphicsScene = static_cast<TGraphicsScene*>(mMainWindow->getCurrentGraphicsScene());
    if(!graphicsScene)
        return;
    graphicsScene->selectObjectItem(objectItem);
    mMainWindow->getCurrentGraphicsView()->centerOn(objectItem);
}
