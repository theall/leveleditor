#include "characterpanelcontroller.h"
#include "../core/core.h"
#include "../core/model/charactermodel.h"
#include "../core/model/itemmodel.h"
#include "../core/model/shotmodel.h"
#include "../core/model/chunkmodel.h"
#include "../core/assets/assetsmanager.h"

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

    connect(core, SIGNAL(ready()), this, SLOT(slotOnCoreReady()));

	mCharacterDock = mainWindow->getCharacterDock();
    connect(mCharacterDock->characterView(), SIGNAL(characterToggled(int,bool)), this,
            SLOT(slotCharacterToggled(int,bool)));

    return TAbstractController::joint(mainWindow, core);
}

void TCharacterPanelController::setCurrentDocument(TDocument *)
{

}

void TCharacterPanelController::slotOnCoreReady()
{
    setFace();
    setItem();
    setShot();
    setChunk();
}

void TCharacterPanelController::slotCharacterToggled(int index, bool)
{
    mCore->characterModel()->setCurrentIndex(index);
}

void TCharacterPanelController::setFace()
{
    TFaceList faceList = mCore->characterModel()->faceList();
    QList<int> idList;
    QList<QPixmap> pixmapList;
    for(TFaceId *faceId : faceList) {
        pixmapList.append(faceId->primitive());
        idList.append(faceId->id());
    }
    mCharacterDock->setPixmapSet(PA_CHARACTER, pixmapList, idList);
}

void TCharacterPanelController::setItem()
{
    TItemIdList itemList = mCore->getItemModel()->itemIdList();
    QList<int> itemidList;
    QList<QPixmap> itempixmapList;
    for(TItemId *itemId : itemList){
        itempixmapList.append(itemId->primitive());
        itemidList.append(itemId->id());
    }
    mCharacterDock->setPixmapSet(PA_ITEM, itempixmapList, itemidList);

}

void TCharacterPanelController::setShot()
{
    TShotList shotList = mCore->shotModel()->shotIdList();
    QList<int> shotidList;
    QList<QPixmap> shotpixmapList;
    for(TShotId *shotId : shotList){
        shotpixmapList.append(shotId->primitive());
        shotidList.append(shotId->id());
    }
    mCharacterDock->setPixmapSet(PA_SHOT,shotpixmapList,shotidList);

}

void TCharacterPanelController::setChunk()
{
    TChunkList chunkList = mCore->chunkModel()->chunIdList();
    QList<int> chunkid;
    QList<QPixmap> chunkpixmapList;
    for(TChunkId *chunkId : chunkList){
        chunkpixmapList.append(chunkId->primitive());
        chunkid.append(chunkId->id());
    }
    mCharacterDock->setPixmapSet(PA_CHUNK,chunkpixmapList,chunkid);
}


void TCharacterPanelController::slotTimerEvent()
{

}
