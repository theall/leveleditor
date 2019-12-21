#include "objectcontroller.h"

#include "../gui/component/objectdock/objectdock.h"
#include "../gui/component/objectdock/objectlistview.h"

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
    connect(mObjectListView, SIGNAL(indexPressed(int)), this, SIGNAL(indexPressed(int)));

    return TAbstractController::joint(mainWindow, core);
}

void TObjectController::setCurrentDocument(TDocument *document)
{
    Q_UNUSED(document);
    if(!document){
        return ;
    }
    TGraphicsScene *graphicsScene = document->graphicsScene();
    mSceneModel = document->getSceneModel();
    connect(graphicsScene, SIGNAL(selectedObjectChanged(TObject*,TObject*)), this, SLOT(slotOnSelectedObjectChanged(TObject*,TObject*)));
}

void TObjectController::setObjectModel(TBaseModel *baseModel)
{
    TBaseModel *basemodel = mSceneModel->getCurrentModel();
    if(TSceneModel *sceneModel = dynamic_cast<TSceneModel*>(basemodel)){
        mObjectListView->setModel(nullptr);
        return ;
    }
    mObjectListView->setModel(baseModel);
}

void TObjectController::slotOnSelectedObjectChanged(TObject *, TObject *current)
{
    TBaseModel *baseModel = mSceneModel->getCurrentModel();
    if(TTileModel *tileModel = dynamic_cast<TTileModel*>(baseModel)){
        mObjectListView->selectRow(tileModel->currentIndex(current));
    } else if(TAreaModel *areaModel = dynamic_cast<TAreaModel*>(baseModel)){
        mObjectListView->selectRow(areaModel->currentIndex(current));
    } else if(TBoxModel *boxModel = dynamic_cast<TBoxModel*>(baseModel)){
        mObjectListView->selectRow(boxModel->currentIndex(current));
    } else if(TDAreaModel *dareaModel = dynamic_cast<TDAreaModel*>(baseModel)){
        mObjectListView->selectRow(dareaModel->currentIndex(current));
    } else if(TPlatModel *platModel = dynamic_cast<TPlatModel*>(baseModel)){
        mObjectListView->selectRow(platModel->currentIndex(current));
    } else if(TWallModel *wallModel = dynamic_cast<TWallModel*>(baseModel)){
        mObjectListView->selectRow(wallModel->currentIndex(current));
    } else if(TRespawnModel *respawModel = dynamic_cast<TRespawnModel*>(baseModel)){
        TRespawnList respawList = respawModel->respawnList();
        for(TRespawn *respawn : respawList){
            if(respawn->respownPointObject() == dynamic_cast<TPointObject*>(current))
            {
                mObjectListView->selectRow(respawList.indexOf(respawn)*2+1);
            }else if(respawn->startPointObject() == dynamic_cast<TPointObject*>(current)){
                mObjectListView->selectRow(respawList.indexOf(respawn)*2+2);
            }
        }
    } else if(TEnemyFactoryModel *enemyFactoryModel = dynamic_cast<TEnemyFactoryModel*>(baseModel)){
        mObjectListView->selectRow(enemyFactoryModel->currentIndex(current));
    } else if(TTriggerModel *triggerModel = dynamic_cast<TTriggerModel*>(baseModel)){
        mObjectListView->selectRow(triggerModel->currentIndex(current));
    }
}

void TObjectController::slotTimerEvent()
{

}
