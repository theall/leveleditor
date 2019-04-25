#include "mapsdockcontroller.h"
#include "../core/core.h"
#include "../gui/component/mapsdock/mapsdock.h"

TMapsDockController::TMapsDockController(QObject *parent) :
    TAbstractController(parent)
  , mMapsModel(nullptr)
{

}

TMapsDockController::~TMapsDockController()
{

}

bool TMapsDockController::joint(TMainWindow *mainWindow, TCore *core)
{
    Q_ASSERT(mainWindow);
    Q_ASSERT(core);

    mMapsProxyView = mainWindow->getMapsDock()->mapsProxyView();
    connect(core, SIGNAL(ready()), this, SLOT(slotOnCoreReady()));
    return TAbstractController::joint(mainWindow, core);
}

void TMapsDockController::setCurrentDocument(TDocument *)
{

}

void TMapsDockController::slotOnCoreReady()
{
    mMapsModel = mCore->mapsModel();
    mMapsProxyView->setModel(mMapsModel);
}

void TMapsDockController::slotOnModuleAdded(TModule *module, int)
{

}

void TMapsDockController::slotOnModuleRemoved(TModule *module, int index)
{

}

void TMapsDockController::slotTimerEvent()
{

}
