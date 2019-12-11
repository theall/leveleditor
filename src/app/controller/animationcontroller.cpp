#include "animationcontroller.h"
#include "../gui/component/animationdock/animationdock.h"
#include "../gui/component/animationdock/container.h"
#include "../gui/component/animationdock/animationlistview.h"
#include "../gui/component/animationdock/framelistview.h"
#include "../gui/component/tabwidget/graphicsview.h"

#include "../core/document/model/animationmodel.h"

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

    mAnimationDock = mainWindow->getAnimationDock();
    connect(mAnimationDock, SIGNAL(requestAdjustFPS(int)), this, SIGNAL(requestAdjustFPS(int)));

    mContainer = mainWindow->getAnimationDock()->getContainer();
    connect(mContainer, SIGNAL(requestAddFrames()), this, SLOT(slotRequestAddFrames()));
    connect(mContainer, SIGNAL(requestAddAnimation()), this, SLOT(slotRequestAddAnimation()));

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

    TAnimation *animation = new TAnimation(animationModel);
    mDocument->cmdAddObject(animation, animationModel);
}

void TAnimationController::slotRequestAddFrames()
{
    TFrameModel *frameModel = static_cast<TFrameModel*>(mFrameListView->model());
    TGraphicsScene *graphicsScene = static_cast<TGraphicsScene*>(mMainWindow->getCurrentGraphicsScene());
    TObjectItemList objectItemList = graphicsScene->getObjectItemList();
    for(TObjectItem *objectItem : objectItemList){
        TTileItem *tileItem = (dynamic_cast<TTileItem*>(objectItem));
        TTile *tile = tileItem->tile();
        frameModel->insetTile(tile,frameModel);
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
