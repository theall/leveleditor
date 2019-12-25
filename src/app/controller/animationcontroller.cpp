#include "animationcontroller.h"
#include "../gui/component/animationdock/animationdock.h"
#include "../gui/component/animationdock/container.h"
#include "../gui/component/animationdock/animationlistview.h"
#include "../gui/component/animationdock/framelistview.h"
#include "../gui/component/tabwidget/graphicsview.h"

#include "../core/document/model/entity/tile.h"
#include "../core/document/model/animationmodel.h"
#include "../core/document/model/tilelayermodel.h"
#include "../core/document/graphics/graphicsscene.h"
#include "../core/document/graphics/layeritem/objectitem/tileitem.h"
#include "../core/document/graphics/layeritem/objectitem/animationitem.h"

TAnimationController::TAnimationController(QObject *parent) :
    TAbstractController(parent)
  , mContainer(nullptr)
  , mAnimationListView(nullptr)
  , mFrameListView(nullptr)
{

}

TAnimationController::~TAnimationController()
{

}

bool TAnimationController::joint(TMainWindow *mainWindow, TCore *core)
{
    Q_ASSERT(mainWindow);
    Q_ASSERT(core);


    mContainer = mainWindow->getAnimationDock()->getContainer();
    connect(mContainer, SIGNAL(requestAddFrames()), this, SLOT(slotRequestAddFrames()));
    connect(mContainer, SIGNAL(requestAddAnimation()), this, SLOT(slotRequestAddAnimation()));
    connect(mContainer, SIGNAL(requestRemoveFrames(QList<int>)), this, SLOT(slotRequestRemoveFrames(QList<int>)));
    connect(mContainer, SIGNAL(requestMoveIndexs(QList<int>, Dir)), this, SLOT(slotRequestMoveIndex(QList<int>, Dir)));

    connect(mContainer, SIGNAL(requestAdjustFPS(int)), this, SIGNAL(requestAdjustFPS(int)));
    connect(mContainer, SIGNAL(requestPlayAnimation()), this, SIGNAL(requestPlayAnimation()));
    connect(mContainer, SIGNAL(requestStopPlayAnimation()), this, SIGNAL(requestStopPlayAnimation()));

    mAnimationListView = mainWindow->getAnimationDock()->getAnimationListView();
    connect(mAnimationListView, SIGNAL(indexPressed(int)), this, SLOT(slotOnAnimationListViewIndexPressed(int)));

    mFrameListView = mainWindow->getAnimationDock()->getFrameListView();
    connect(mFrameListView, SIGNAL(indexPressed(int)), this, SLOT(slotOnFrameListViewIndexPressed(int)));

    return TAbstractController::joint(mainWindow, core);
}

void TAnimationController::setCurrentDocument(TDocument *document)
{
    if(!document)
    {
        // Insert stub code here
        mAnimationListView->setModel(nullptr);
        mFrameListView->setModel(nullptr);
        return;
    }
    if(mDocument != document)
    {
        mAnimationListView->setModel(document->getSceneModel()->getAnimationsModel());
        mFrameListView->setModel(nullptr);
    }
    TGraphicsScene *graphicsScene = document->graphicsScene();
    connect(graphicsScene, SIGNAL(selectedObjectChanged(TObject*, TObject*)), this, SLOT(slotOnSelectedObjectChanged(TObject*, TObject*)));
}

void TAnimationController::slotOnAnimationListViewIndexPressed(int index)
{
    if(!mDocument)
        return;

    TAnimationModel *animationModel = getAnimationModel();
    if(!animationModel)
        return;

    TFrameModel *frameModel = animationModel->getFrameModel(index);
    if(!frameModel)
        return;

    mFrameListView->setModel(frameModel);

    TTile *tile = frameModel->animation()->getTile();
    TObjectItem *objectItem = TObjectItem::getObjectItem(tile);
    selectAndCenterOn(objectItem);

    // Notify main controller to set property sheet to main property controller
    emit requestDisplayPropertySheet(frameModel->getPropertySheet());
}

void TAnimationController::slotOnFrameListViewIndexPressed(int index)
{
    if(!mDocument)
        return;

    TFrameModel *frameModel = static_cast<TFrameModel*>(mFrameListView->model());
    if(!frameModel)
        return;

    TObjectItem *objectItem = TObjectItem::getObjectItem(frameModel->animation()->getFrameTile(index));
    selectAndCenterOn(objectItem);

    // Notify main controller to set property sheet to main property controller
    emit requestDisplayPropertySheet(frameModel->getFramePropertySheet(index));
}

TAnimationModel *TAnimationController::getAnimationModel() const
{
    return static_cast<TAnimationModel*>(mAnimationListView->model());
}

void TAnimationController::slotRequestAddAnimation()
{
    TAnimationModel *animationModel = getAnimationModel();
    if(!animationModel)
        return;

    TGraphicsScene *graphicsScene = static_cast<TGraphicsScene*>(mMainWindow->getCurrentGraphicsScene());
    TObjectItemList objectItemList = graphicsScene->getSelectedObjectItemList();
    TTileItemList tileItemList;
    for(TObjectItem *objectItem : objectItemList) {
        TTileItem *tileItem = dynamic_cast<TTileItem*>(objectItem);
        tileItemList.append(tileItem);
    }
    if(!tileItemList.size())
        return;

    TSceneModel *sceneModel = mDocument->getSceneModel();
    TBaseModel *baseModel = sceneModel->getCurrentModel();
    TObjectList objectList;

    if(TTileModel *tileModel = dynamic_cast<TTileModel*>(baseModel)) {
        for(TTileItem *tileItem : tileItemList) {
            TTile *tile = tileItem->tile();
            TAnimation *animation = new TAnimation(animationModel);
            objectList.append(animation);
            TTileList tileList = tileModel->tileList();
            TBaseModelList baseModelList = sceneModel->getBaseModelList();
            animation->setTile(tile);
            animation->setTileLayer(baseModelList.indexOf(baseModel));
            animation->setTileNumber(tileList.indexOf(tile));
            mContainer->setNewButtonAnimation(true);
        }
        mDocument->cmdAddObject(objectList, animationModel);
    }
    return;
}

void TAnimationController::slotRequestAddFrames()
{
    TSceneModel *sceneModel = mDocument->getSceneModel();
    TBaseModel *baseModel = sceneModel->getCurrentModel();
    if(TTileModel *tileModel = dynamic_cast<TTileModel*>(baseModel)) {
        TFrameModel *frameModel = static_cast<TFrameModel*>(mFrameListView->model());
        TGraphicsScene *graphicsScene = static_cast<TGraphicsScene*>(mMainWindow->getCurrentGraphicsScene());
        TObjectItemList objectItemList = graphicsScene->getSelectedObjectItemList();
        TObjectList objectList;
        for(TObjectItem *objectItem : objectItemList) {
            TTileItem *tileItem = (dynamic_cast<TTileItem*>(objectItem));
            TTile *tile = tileItem->tile();
            TFrame *frame = new TFrame(tile, frameModel);
            objectList.append(frame);
        }
        mDocument->cmdAddObject(objectList, frameModel);
    }
}

void TAnimationController::slotOnSelectedObjectChanged(TObject *, TObject *)
{
    TSceneModel *sceneModel = mDocument->getSceneModel();
    TBaseModel *baseModel = sceneModel->getCurrentModel();
    if(TTileModel *tileModel = dynamic_cast<TTileModel*>(baseModel)) {
        TGraphicsScene *graphicsScene = static_cast<TGraphicsScene*>(mMainWindow->getCurrentGraphicsScene());
        for(TObjectItem *objectItem : graphicsScene->getSelectedObjectItemList()) {
            TAnimationItem *aniamtionItem = dynamic_cast<TAnimationItem*>(objectItem);
            if(aniamtionItem) {
                mContainer->setNewButtonAnimation(true);
                return;
            }
        }
        mContainer->setNewButtonAnimation(false);
    }
}

void TAnimationController::slotRequestRemoveFrames(const QList<int> &indexList)
{
    TFrameModel *frameModel = static_cast<TFrameModel*>(mFrameListView->model());
    TObjectList objectList;
    for(int index : indexList) {
        TFrame *frame = frameModel->getFrame(index);
        objectList.append(frame);
    }
    mDocument->cmdRemoveObject(objectList, frameModel);
}

void TAnimationController::slotRequestMoveIndex(const QList<int> &indexList, const Dir &dir)
{
    if(dir == Dir::Up) {

    } else if(dir == Dir::Down) {

    } else if(dir == Dir::Left) {

    } else if(dir == Dir::Right) {

    }
}

void TAnimationController::selectAndCenterOn(TObjectItem *objectItem)
{
    if(!objectItem)
        return;

    TGraphicsScene *graphicsScene = static_cast<TGraphicsScene*>(mMainWindow->getCurrentGraphicsScene());
    if(!graphicsScene)
        return;
    graphicsScene->selectObjectItem(objectItem);
    mMainWindow->getCurrentGraphicsView()->centerOn(objectItem);
}

void TAnimationController::slotTimerEvent()
{

}
