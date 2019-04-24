#include "characterpanelcontroller.h"
#include "../core/core.h"
#include "../gui/component/characterdock/characterview.h"
#include "../gui/component/characterdock/characterdock.h"

TCharacterPanelController::TCharacterPanelController(QObject *parent) :
    TAbstractController(parent)
  , mCharacterPanel(nullptr)
{

}

TCharacterPanelController::~TCharacterPanelController()
{

}

bool TCharacterPanelController::joint(TMainWindow *mainWindow, TCore *core)
{
    Q_ASSERT(mainWindow);
    Q_ASSERT(core);
    mCharacterPanel = mainWindow->getCharacterDock()->characterView();

    connect(core, SIGNAL(ready()), this, SLOT(slotOnCoreReady()));
    return TAbstractController::joint(mainWindow, core);
}

void TCharacterPanelController::setCurrentDocument(TDocument *)
{

}

void TCharacterPanelController::slotOnCoreReady()
{
    for(TFaceId *faceId : mCore->characterModel()->faceList()) {
        mCharacterPanel->add(faceId->pixmap()->content());
    }
}

void TCharacterPanelController::slotTimerEvent()
{

}
