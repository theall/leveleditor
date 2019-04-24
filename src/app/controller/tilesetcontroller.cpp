#include "tilesetcontroller.h"
#include "../core/core.h"
#include "../gui/component/tilesetdock/tilesetdock.h"

TTilesetController::TTilesetController(QObject *parent) :
    TAbstractController(parent)
  , mTilesetTab(nullptr)
{

}

TTilesetController::~TTilesetController()
{

}

bool TTilesetController::joint(TMainWindow *mainWindow, TCore *core)
{
    Q_ASSERT(mainWindow);
    Q_ASSERT(core);
    mTilesetTab = mainWindow->getTilesetDock()->tilesetTab();

    connect(core, SIGNAL(ready()), this, SLOT(slotOnCoreReady()));
    return TAbstractController::joint(mainWindow, core);
}

void TTilesetController::setCurrentDocument(TDocument *)
{

}

void TTilesetController::slotOnCoreReady()
{
    int index = 1;
    for(TTilesetModel *tilesetModel : mCore->tilesetModelList()) {
        mTilesetTab->addTab(tilesetModel, QString::number(index++));
    }
}

void TTilesetController::slotTimerEvent()
{

}
