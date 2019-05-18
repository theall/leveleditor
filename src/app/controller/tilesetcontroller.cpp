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
    connect(mTilesetTab, SIGNAL(onTilesetViewRowChanged(int,int)), this, SLOT(slotonTilesetViewCurrentRowChanged(int,int)));

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

void TTilesetController::slotonTilesetViewCurrentRowChanged(int tileset, int row)
{
    TTilesetModelList tilesetModelList = mCore->tilesetModelList();
    TTilesetModel *tilesetModel =  tilesetModelList.at(tileset);
    if(!tilesetModel)
        return;

    TTileId *tileId = tilesetModel->getTileId(row);
    mDocument->setTileStamp(tileId);
}

void TTilesetController::slotTimerEvent()
{

}
