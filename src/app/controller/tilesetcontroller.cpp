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

void TTilesetController::setTilesetEnabled(bool enabled)
{
    mTilesetTab->setEnabled(enabled);
}

bool TTilesetController::joint(TMainWindow *mainWindow, TCore *core)
{
    Q_ASSERT(mainWindow);
    Q_ASSERT(core);
    mTilesetTab = mainWindow->getTilesetDock()->tilesetTab();
    connect(mTilesetTab, SIGNAL(onTilesetViewRowChanged(int,int)), this, SLOT(slotOnTilesetViewCurrentRowChanged(int,int)));

    connect(core, SIGNAL(ready()), this, SLOT(slotOnCoreReady()));
    return TAbstractController::joint(mainWindow, core);
}

void TTilesetController::setCurrentDocument(TDocument *document)
{
    if(document && document->getEditMode()==INSERT) {
        TTileId *tileId = mCore->tilesetModelManager()->getCurrentTileId();
        document->setTileStamp(tileId);
    }
}

void TTilesetController::slotOnCoreReady()
{
    int index = 1;
    TTilesetModelList tilesetModelList = mCore->tilesetModelList();
    for(TTilesetModel *tilesetModel : tilesetModelList) {
        mTilesetTab->addTab(tilesetModel, QString::number(index++));
    }

    mTilesetTab->selectTile(0, 0);
}

void TTilesetController::slotOnTilesetViewCurrentRowChanged(int tileset, int row)
{
    TTilesetModelManager *tilesetModelManager = mCore->tilesetModelManager();
    tilesetModelManager->setCurrentIndex(tileset, row);
    TTileId *tileId = tilesetModelManager->getTileId(tileset, row);
    if(mDocument)
        mDocument->setTileStamp(tileId);
}

void TTilesetController::slotTimerEvent()
{

}
