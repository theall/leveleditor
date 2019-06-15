#include "animationcontroller.h"
#include "../gui/component/animationdock/animationdock.h"
#include "../gui/component/animationdock/animationlistview.h"
#include "../gui/component/animationdock/framelistview.h"
#include "../gui/component/tabwidget/graphicsview.h"

TAnimationController::TAnimationController(QObject *parent) :
    TAbstractController(parent)
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

    TAnimationModel *animationModel = static_cast<TAnimationModel*>(mAnimationListView->model());
    if(!animationModel)
        return;

    TFrameModel *frameModel = animationModel->getFrameModel(index);
    mFrameListView->setModel(frameModel);

    TObjectItem *objectItem = TObjectItem::getObjectItem(frameModel->animation()->getTile());
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

void TAnimationController::selectAndCenterOn(TObjectItem *objectItem)
{
    TGraphicsScene *graphicsScene = static_cast<TGraphicsScene*>(mMainWindow->getCurrentGraphicsScene());
    if(!graphicsScene)
        return;
    graphicsScene->selectObjectItem(objectItem);
    mMainWindow->getCurrentGraphicsView()->centerOn(objectItem);
}

void TAnimationController::slotTimerEvent()
{

}
