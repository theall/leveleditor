#include "objectcontroller.h"

#include "../gui/component/objectdock/objectdock.h"
#include "../gui/component/objectdock/objectlistview.h"

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
    TGraphicsScene *graphicsScene = document->graphicsScene();
    connect(graphicsScene, SIGNAL(selectedObjectChanged(TObject*,TObject*)), this, SLOT(slotOnSelectedObjectChanged(TObject*,TObject*)));
}

void TObjectController::setObjectModel(TBaseModel *baseModel)
{
    mObjectListView->setModel(baseModel);
}

void TObjectController::slotOnSelectedObjectChanged(TObject *, TObject *current)
{
    TBaseModel *currentModel = mSceneModel->getCurrentModel();
}

void TObjectController::slotTimerEvent()
{

}
