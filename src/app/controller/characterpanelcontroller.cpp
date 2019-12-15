#include "characterpanelcontroller.h"
#include "../core/core.h"
#include "../core/model/charactermodel.h"
#include "../core/model/itemmodel.h"
#include "../core/model/shotmodel.h"
#include "../core/model/chunkmodel.h"

#include "../gui/component/characterdock/characterview.h"
#include "../gui/component/characterdock/characterdock.h"

template<typename T>
QList<QPixmap> toPixmapList(const QList<T> &pixmapIdList) {
    QList<QPixmap> pixmapList;
    for(T pixmapId : pixmapIdList) {
        pixmapList.append(pixmapId->primitive());
    }
    return pixmapList;
}

TCharacterPanelController::TCharacterPanelController(QObject *parent) :
    TAbstractController(parent)
  , mCharacterDock(nullptr)
{

}

TCharacterPanelController::~TCharacterPanelController()
{

}

bool TCharacterPanelController::joint(TMainWindow *mainWindow, TCore *core)
{
    Q_ASSERT(mainWindow);
    Q_ASSERT(core);
    mCharacterDock = mainWindow->getCharacterDock();

    connect(core, SIGNAL(ready()), this, SLOT(slotOnCoreReady()));
    return TAbstractController::joint(mainWindow, core);
}

void TCharacterPanelController::setCurrentDocument(TDocument *)
{

}

void TCharacterPanelController::slotOnCoreReady()
{
    mCharacterDock->setPixmapSet(PA_CHARACTER, toPixmapList<TFaceId*>(mCore->characterModel()->faceList()));
    mCharacterDock->setPixmapSet(PA_ITEM, toPixmapList<TItemId*>(mCore->getItemModel()->itemIdList()));
    mCharacterDock->setPixmapSet(PA_SHOT, toPixmapList<TShotId*>(mCore->shotModel()->shotIdList()));
    mCharacterDock->setPixmapSet(PA_CHUNK, toPixmapList<TChunkId*>(mCore->chunkModel()->chunIdList()));
}

void TCharacterPanelController::slotTimerEvent()
{

}
