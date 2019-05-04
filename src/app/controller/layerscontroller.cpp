#include "layerscontroller.h"
#include "gui/component/layerdock/layerdock.h"
#include "gui/component/layerdock/layerview.h"

TLayersController::TLayersController(QObject *parent) :
    TAbstractController(parent)
  , mLayerView(nullptr)
{

}

TLayersController::~TLayersController()
{

}

bool TLayersController::joint(TMainWindow *mainWindow, TCore *core)
{
    Q_ASSERT(mainWindow);
    Q_ASSERT(core);

    mLayerView = mainWindow->getLayerDock()->layerView();
    return TAbstractController::joint(mainWindow, core);
}

void TLayersController::setCurrentDocument(TDocument *document)
{
    if(mDocument == document)
        return;

    if(mDocument)
        mDocument->disconnect(this);

    QAbstractItemModel *model = nullptr;

    if(document)
    {
        model = document->getSceneModel();
    }
    mLayerView->setModel(model);
}

void TLayersController::slotTimerEvent()
{

}
