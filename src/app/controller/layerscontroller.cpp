#include "layerscontroller.h"

TLayersController::TLayersController(QObject *parent) :
    TAbstractController(parent)
{

}

TLayersController::~TLayersController()
{

}

bool TLayersController::joint(TMainWindow *mainWindow, TCore *core)
{
    Q_ASSERT(mainWindow);
    Q_ASSERT(core);

    return TAbstractController::joint(mainWindow, core);
}

void TLayersController::setCurrentDocument(TDocument *)
{

}

void TLayersController::slotTimerEvent()
{

}
