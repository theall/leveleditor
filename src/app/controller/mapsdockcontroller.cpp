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
    Q_ASSERT(mMapsProxyView);
    connect(mMapsProxyView,
            SIGNAL(modelIndexDoubleClicked(QModelIndex)),
            this,
            SLOT(slotOnModelIndexDoubleClicked(QModelIndex)));

    mMapsModel = core->mapsModel();
    Q_ASSERT(mMapsModel);
    connect(mMapsModel, SIGNAL(moduleAdded(TModule*,int)), this, SLOT(slotOnModuleAdded(TModule*,int)));
    connect(mMapsModel, SIGNAL(moduleRemoved(TModule*,int)), this, SLOT(slotOnModuleRemoved(TModule*,int)));

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

void TMapsDockController::slotOnModelIndexDoubleClicked(const QModelIndex &index)
{
    if(!mMapsModel)
        return;

    TMap *map = dynamic_cast<TMap*>((QObject*)index.internalPointer());
    if(map) {
        emit requestOpenMap(map);
    }
}

void TMapsDockController::slotOnModuleAdded(TModule *, int)
{

}

void TMapsDockController::slotOnModuleRemoved(TModule *, int)
{

}

void TMapsDockController::slotTimerEvent()
{

}
