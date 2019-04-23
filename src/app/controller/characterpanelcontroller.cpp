#include "characterpanelcontroller.h"
#include "../core/assets/assetsmanager.h"
#include "../gui/component/characterdock/characterview.h"
#include "../gui/component/characterdock/characterdock.h"

TCharacterPanelController::TCharacterPanelController(QObject *parent) :
    TAbstractController(parent)
  , mCharacterPanel(nullptr)
{
    connect(TAssetsManager::getInstance(), SIGNAL(loadCompleted()), this, SLOT(slotOnResourceLoadCompleted()));
}

TCharacterPanelController::~TCharacterPanelController()
{

}

bool TCharacterPanelController::joint(TMainWindow *mainWindow, TCore *core)
{
    Q_ASSERT(mainWindow);
    Q_ASSERT(core);
    mCharacterPanel = mainWindow->getCharacterDock()->characterView();

    return TAbstractController::joint(mainWindow, core);
}

void TCharacterPanelController::setCurrentDocument(TDocument *)
{

}

void TCharacterPanelController::slotOnResourceLoadCompleted()
{
    for(TFaceId *faceId: TAssetsManager::getInstance()->getFaceList()) {
        mCharacterPanel->add(faceId->pixmap()->content());
    }
}

void TCharacterPanelController::slotTimerEvent()
{

}
