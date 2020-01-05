#include "tilesetcontroller.h"

#include "../core/core.h"
#include "../core/document/model/entity/tile.h"
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

TTileId *TTilesetController::getCurrentTileId() const
{
    TTilesetModelManager *tilesetModelManager = mCore->tilesetModelManager();
    return tilesetModelManager->currentTilesetModel()->getCurrentTileId();
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
    if(mDocument)
        mDocument->disconnect(this);

    if(document) {
//        if(document->getEditMode()==INSERT) {
//            TTileId *tileId = mCore->tilesetModelManager()->getCurrentTileId();
//            document->setTileStamp(tileId);
//        }

        TGraphicsScene *graphicsScene = document->graphicsScene();
        connect(graphicsScene, SIGNAL(selectedObjectChanged(TObject*,TObject*)), this, SLOT(slotOnSelectedObjectChanged(TObject*,TObject*)));
    }
}

void TTilesetController::slotOnCoreReady()
{
    int index = 1;
    TTilesetModelList tilesetModelList = mCore->tilesetModelList();
    for(TTilesetModel *tilesetModel : tilesetModelList) {
        mTilesetTab->addTab(tilesetModel, QString::number(index++));
    }

    mTilesetTab->selectIndex(0, 0);
}

void TTilesetController::slotOnTilesetViewCurrentRowChanged(int tileset, int row)
{
    TTilesetModelManager *tilesetModelManager = mCore->tilesetModelManager();
    tilesetModelManager->setCurrentIndex(tileset, row);
    TTileId *tileId = tilesetModelManager->getTileId(tileset, row);
    if(mDocument)
        mDocument->setTileStamp(tileId);
}

void TTilesetController::slotOnSelectedObjectChanged(TObject *, TObject *current)
{
    // Check if object is tile object
    if(current && current->type()==TObject::TILE) {
        TTile *tile = static_cast<TTile*>(current);
        TTileId *tileId = tile->tileId();
        int tilesetIndex, tileIdIndex;
        bool found = mCore->tilesetModelManager()->findTileIdIndex(tileId, tilesetIndex, tileIdIndex);
        if(found) {
            mTilesetTab->selectIndex(tilesetIndex, tileIdIndex);
        }
    }
}

void TTilesetController::slotTimerEvent()
{

}
