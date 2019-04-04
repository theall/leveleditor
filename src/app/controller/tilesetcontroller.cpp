#include "tilesetcontroller.h"
#include "../core/assets/assetsmanager.h"
#include "../gui/component/tilesetdock/tilesetdock.h"

TTilesetController::TTilesetController(QObject *parent) :
    TAbstractController(parent)
  , mTilesetTab(nullptr)
{
    connect(TAssetsManager::getInstance(), SIGNAL(loadCompleted()), this, SLOT(slotOnResourceLoadCompleted()));
}

TTilesetController::~TTilesetController()
{

}

bool TTilesetController::joint(TMainWindow *mainWindow, TCore *core)
{
    Q_ASSERT(mainWindow);
    Q_ASSERT(core);
    mTilesetTab = mainWindow->getTilesetDock()->tilesetTab();

    return TAbstractController::joint(mainWindow, core);
}

void TTilesetController::setCurrentDocument(TDocument *)
{

}

void TTilesetController::slotOnResourceLoadCompleted()
{
    int index = 1;
    for(TTilesetModel *tilesetModel : TAssetsManager::getInstance()->getTilesetModelList()) {
        mTilesetTab->addTab(tilesetModel, QString::number(index++));
    }
}

void TTilesetController::slotTimerEvent()
{

}
