#include "mapsdockcontroller.h"
#include "../core/core.h"

TMapsDockController::TMapsDockController(QObject *parent) :
    TAbstractController(parent)
{

}

TMapsDockController::~TMapsDockController()
{

}

bool TMapsDockController::joint(TMainWindow *mainWindow, TCore *core)
{
    Q_ASSERT(mainWindow);
    Q_ASSERT(core);

    connect(core, SIGNAL(ready()), this, SLOT(slotOnCoreReady()));
    return TAbstractController::joint(mainWindow, core);
}

void TMapsDockController::setCurrentDocument(TDocument *)
{

}

void TMapsDockController::slotOnCoreReady()
{

}

void TMapsDockController::slotTimerEvent()
{

}
