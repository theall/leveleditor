#include "soundsetcontroller.h"
#include "../core/document/model/sound/soundset.h"
#include "../gui/component/sounddock/sounddock.h"
#include "../gui/component/sounddock/soundsetview.h"
#include "../gui/dialogs/soundresourcedialog.h"

TSoundSetController::TSoundSetController(QObject *parent) :
    TAbstractController(parent)
  , mSoundSet(nullptr)
  , mSoundSetView(nullptr)
  , mPropertyController(new TPropertyController(this))
  , mSoundResourceDialog(nullptr)
{
    connect(mPropertyController,
            SIGNAL(propertyItemValueChanged(TPropertyItem*,QVariant)),
            this,
            SLOT(slotPropertyItemValueChanged(TPropertyItem*,QVariant)));
}

TSoundSetController::~TSoundSetController()
{

}

bool TSoundSetController::joint(TMainWindow *mainWindow, TCore *core)
{
    Q_ASSERT(mainWindow);
    Q_ASSERT(core);

    TSoundDock *soundDock = mainWindow->soundDock();
    connect(soundDock,
            SIGNAL(requestAddSoundItems()),
            this,
            SLOT(slotRequestAddSoundItems()));
    connect(soundDock,
            SIGNAL(requestRemoveSoundItems(QList<int>)),
            this,
            SLOT(slotRequestRemoveSoundItems(QList<int>)));

    //mSoundResourceDialog = mainWindow->getSoundResourceDialog();
    mSoundSetView = soundDock->soundSetView();
    connect(mSoundSetView, SIGNAL(rowSelected(int)), this, SLOT(slotRowSelected(int)));

    mPropertyController->setPropertyBrowser(soundDock->propertyBrowser());
    return TAbstractController::joint(mainWindow, core);
}

void TSoundSetController::setCurrentDocument(TDocument *document)
{
    mPropertyController->setCurrentDocument(document);

    if(document == nullptr)
    {
        mSoundSetView->setModel(nullptr);
        if(mSoundSet)
        {
            mSoundSet->disconnect(this);
            mSoundSet = nullptr;
        }
    }
}

void TSoundSetController::slotRequestAddSoundItems()
{
    if(!mSoundResourceDialog || !mSoundSet)
        return;

    QStringList selectedSoundList = mSoundResourceDialog->getSelectedSounds();
    QList<TSound *> soundList;
    for(QString file : selectedSoundList)
    {
        TSound *s = mDocument->getSound(file);
        if(s)
            soundList.append(s);
    }
    if(soundList.size() > 0) {
        mSoundSet->soundItemsModel()->cmdAddSoundList(soundList);
    }
}

void TSoundSetController::slotRequestRemoveSoundItems(const QList<int> &indexList)
{
    if(!mSoundSetView || !mSoundSet)
        return;

    TSoundItemList soundItemList;
    TSoundItemsModel *soundItemsModel = mSoundSet->soundItemsModel();
    for(int index : indexList)
    {
        TSoundItem *soundItem = soundItemsModel->getSoundItem(index);
        if(soundItem)
            soundItemList.append(soundItem);
    }
    if(soundItemList.size() > 0)
        mSoundSet->soundItemsModel()->cmdRemoveSoundList(soundItemList);
}

void TSoundSetController::slotRowSelected(int index)
{
    if(!mSoundSet)
        return;

    TSoundItemsModel *soundItemsModel = mSoundSet->soundItemsModel();
    if(!soundItemsModel)
        return;

    TSoundItem *soundItem = soundItemsModel->getSoundItem(index);
    mPropertyController->setPropertySheet(soundItem?soundItem->propertySheet():mSoundSet->propertySheet());
}

TSoundSet *TSoundSetController::soundSet() const
{
    return mSoundSet;
}

void TSoundSetController::setSoundSet(TSoundSet *soundSet)
{
    if(mSoundSet == soundSet)
        return;

    if(mSoundSet)
        mSoundSet->disconnect(this);

    mSoundSet = soundSet;

    if(mSoundSet)
    {
        TSoundItemsModel *soundItemsModel = soundSet->soundItemsModel();
        mSoundSetView->setModel(soundItemsModel);
        if(soundItemsModel)
        {
            slotRowSelected(-1);
            connect(soundItemsModel,
                    SIGNAL(soundItemsAdded(TSoundItemList,QList<int>)),
                    this,
                    SLOT(slotSoundItemsAdded(TSoundItemList,QList<int>)));
            connect(soundItemsModel,
                    SIGNAL(soundItemsRemoved(TSoundItemList,QList<int>)),
                    this,
                    SLOT(slotSoundItemsRemoved(TSoundItemList,QList<int>)));
        }
    } else {
        mSoundSetView->setModel(nullptr);
    }
}

void TSoundSetController::slotPropertyItemValueChanged(TPropertyItem *propertyItem, const QVariant &newValue)
{
    if(!propertyItem || !mDocument)
        return;

    TPropertySheet *propertySheet = qobject_cast<TPropertySheet*>(propertyItem->parent());
    if(!propertySheet)
        return;

    TPropertyUndoCommand *undoCommand = new TPropertyUndoCommand(
                propertyItem,
                propertyItem->propertyId(),
                newValue);
    mDocument->addUndoCommand(undoCommand);
}

void TSoundSetController::slotSoundItemsAdded(const TSoundItemList &soundItemList, const QList<int> indexList)
{
    Q_UNUSED(soundItemList);
    Q_UNUSED(indexList);
}

void TSoundSetController::slotSoundItemsRemoved(const TSoundItemList &soundItemList, const QList<int> indexList)
{
    Q_UNUSED(soundItemList);
    Q_UNUSED(indexList);
    slotRowSelected(-1);
}

void TSoundSetController::slotTimerEvent()
{

}
