#include "characterpanelcontroller.h"
#include "../core/core.h"
#include "../core/model/charactermodel.h"
#include "../core/model/itemmodel.h"
#include "../core/model/shotmodel.h"
#include "../core/model/chunkmodel.h"
#include "../core/assets/assetsmanager.h"

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

void TCharacterPanelController::setCharacterEnabled(bool enabled)
{
    mCharacterDock->setEnabled(enabled);
}

TPixmapId *TCharacterPanelController::getCurrentPixmapId() const
{
    PanelType panelType = mCharacterDock->getCurrentPanelType();
    if(panelType == PA_CHARACTER) {
        return mCore->characterModel()->getCurrentFaceId();
    } else if(panelType == PA_ITEM) {
        return mCore->ItemModel()->getCurrentItemId();
    } else if(panelType == PA_SHOT) {
        return mCore->shotModel()->getCurrentShotId();
    } else if(panelType == PA_CHUNK) {
        return mCore->chunkModel()->getCurrentChunkId();
    }

    return nullptr;
}


bool TCharacterPanelController::joint(TMainWindow *mainWindow, TCore *core)
{
    Q_ASSERT(mainWindow);
    Q_ASSERT(core);

    connect(core, SIGNAL(ready()), this, SLOT(slotOnCoreReady()));

	mCharacterDock = mainWindow->getCharacterDock();
    connect(mCharacterDock,
            SIGNAL(buttonPushed(PanelType,int)),
            this,
            SLOT(slotButtonPushed(PanelType,int)));

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

void TCharacterPanelController::slotButtonPushed(const PanelType &panelType, int index)
{
    if(!mDocument)
        return;

    switch (panelType) {
    case PA_CHARACTER:
        mCore->characterModel()->setCurrentIndex(index);
        mDocument->setFaceStamp(mCore->characterModel()->getCurrentFaceId());
        break;
    case PA_ITEM:
        mCore->ItemModel()->setCurrentIndex(index);
        mDocument->setItemStamp(mCore->ItemModel()->getCurrentItemId());
        break;
    case PA_CHUNK:
        mCore->chunkModel()->setCurrentIndex(index);
        mDocument->setChunkStamp(mCore->chunkModel()->getCurrentChunkId());
        break;
    case PA_SHOT:
        mCore->shotModel()->setCurrentIndex(index);
        mDocument->setShotStamp(mCore->shotModel()->getCurrentShotId());
        break;
    default:
        break;
    }
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
    TItemIdList itemList = mCore->ItemModel()->itemIdList();
    QList<int> itemidList;
    QList<QPixmap> itempixmapList;
    for(TItemId *itemId : itemList) {
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
    for(TShotId *shotId : shotList) {
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
