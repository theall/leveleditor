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
    connect(mSubControlObjectListView, SIGNAL(indexPressed(int)), this, SLOT(slotEnemyIndexPressed(int)));


    return TAbstractController::joint(mainWindow, core);
}

void TObjectController::setCurrentDocument(TDocument *document)
{
    if(!document)
        return;

    TGraphicsScene *graphicsScene = document->graphicsScene();
    mSceneModel = document->getSceneModel();
    setObjectListViewModel(nullptr);
    setSubControlObjectListViewModel(nullptr);
    connect(graphicsScene, SIGNAL(selectedObjectChanged(TObject*,TObject*)), this, SLOT(slotOnSelectedObjectChanged(TObject*,TObject*)));
}

void TObjectController::resetCurrentModel()
{
    TBaseModel *baseModel = mSceneModel->getCurrentModel();
    setObjectListViewModel(baseModel);
    if(dynamic_cast<TEnemyFactoryModel*>(baseModel))
        setSubControlObjectListViewModel(nullptr);

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

void TObjectController::setSubControlObjectListViewModel(TEnemyModel *enemyModel)
{
    mSubControlObjectListView->setModel(enemyModel);
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
        mObjectListView->selectRow(respawModel->pointObjectIndex(dynamic_cast<TPointObject*>(current)), parent);
    } else if(TEnemyFactoryModel *enemyFactoryModel = dynamic_cast<TEnemyFactoryModel*>(baseModel)) {
        mObjectListView->selectRow(enemyFactoryModel->currentIndex(current), parent);
    } else if(TTriggerModel *triggerModel = dynamic_cast<TTriggerModel*>(baseModel)) {
        mObjectListView->selectRow(triggerModel->currentIndex(current), parent);
    }
}

void TObjectController::slotObjectIndexPressed(const QModelIndex &index)
{
    if(!mDocument)
        return;

    TBaseModel *baseModel = mSceneModel->getCurrentModel();

    // Select and center object items
    TObjectList objectList;
    for(int row : mObjectListView->getSelectedIndexes()) {
        if(TTileModel *tileModel = dynamic_cast<TTileModel*>(baseModel)) {
            objectList.append(tileModel->getObject(row));
        } else if(TAreaModel *areaModel = dynamic_cast<TAreaModel*>(baseModel)) {
            objectList.append(areaModel->getObject(row));
        } else if(TBoxModel *boxModel = dynamic_cast<TBoxModel*>(baseModel)) {
            objectList.append(boxModel->getObject(row));
        } else if(TDAreaModel *dareaModel = dynamic_cast<TDAreaModel*>(baseModel)) {
            objectList.append(dareaModel->getObject(row));
        } else if(TPlatModel *platModel = dynamic_cast<TPlatModel*>(baseModel)) {
            objectList.append(platModel->getObject(row));
        } else if(TWallModel *wallModel = dynamic_cast<TWallModel*>(baseModel)) {
            objectList.append(wallModel->getObject(row));
        } else if(TRespawnModel *respawnModel = dynamic_cast<TRespawnModel*>(baseModel)) {
            objectList.append(respawnModel->getObject(row));
        } else if(TEnemyFactoryModel *enemyFactoryModel = dynamic_cast<TEnemyFactoryModel*>(baseModel)) {
            objectList.append(enemyFactoryModel->getObject(row));
            setSubControlObjectListViewModel(enemyFactoryModel->getEnemyModel(row));
        } else if(TTriggerModel *triggerModel = dynamic_cast<TTriggerModel*>(baseModel)) {
            objectList.append(triggerModel->getObject(row));
        }
    }
    selectAndCenterOn(objectList);

    // Sychronize index into enemy factory model
    if(baseModel->type() == TBaseModel::ENEMY_FACTORY) {
        int row = index.row();
        TEnemyFactoryModel *enemyFactoryModel = mDocument->getSceneModel()->getEnemyFactoryModel();
        enemyFactoryModel->setCurrentIndex(row);
    }
}

void TObjectController::slotEnemyIndexPressed(int index)
{
    TBaseModel *baseModel = mSceneModel->getCurrentModel();
    TObjectList objectList;

    if(TEnemyFactoryModel *enemyFactoryModel = dynamic_cast<TEnemyFactoryModel*>(baseModel)) {
        int enemyFactoryIndex = mObjectListView->getCurrentIndex();
        TEnemyFactory *enemyFactory = enemyFactoryModel->getEnemyFactory(enemyFactoryIndex);
        for(int row : mSubControlObjectListView->getSelectedIndexes()){
            objectList.append(enemyFactory->getEnemy(row));
        }
    }
    selectAndCenterOn(objectList);
}

void TObjectController::slotTimerEvent()
{

}

void TObjectController::selectAndCenterOn(TObjectList &objectList)
{
    TObjectItemList objectItemList;
    TObjectItem *objectItem;
    for(TObject *object : objectList) {
        objectItem = TObjectItem::getObjectItem(object);
        objectItemList.append(objectItem);
        if(!objectItem)
            return;
    }

    TGraphicsScene *graphicsScene = static_cast<TGraphicsScene*>(mMainWindow->getCurrentGraphicsScene());
    if(!graphicsScene)
        return;
    graphicsScene->selectObjectItemList(objectItemList);
    mMainWindow->getCurrentGraphicsView()->centerOn(objectItem);
}
