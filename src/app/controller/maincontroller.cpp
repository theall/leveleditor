#include "maincontroller.h"
#include "../utils/preferences.h"
#include "../gui/dialogs/selectrootdialog.h"
#include "../gui/dialogs/loadingdialog.h"
#include "../gui/dialogs/newmapdialog.h"
#include "../gui/component/tabwidget/tabwidget.h"
#include "../gui/component/characterdock/characterdock.h"
#include "../gui/component/characterdock/characterview.h"
#include "../core/assets/assetsmanager.h"
#include "../core/model/charactermodel.h"
#include "../core/model/itemmodel.h"
#include "../core/document/graphics/layeritem/objectitem/tileitem.h"

#include <QProcess>
#include <QMessageBox>
#include <QCoreApplication>

TMainController::TMainController(QObject *parent) :
    TAbstractController(parent)
  , mOptionsController(new TOptionsController(this))
  , mTabController(new TTabController(this))
  , mMainPropertyController(new TMainPropertyController(this))
  , mUndoController(new TUndoController(this))
  , mMiniSceneController(new TMiniSceneController(this))
  , mTilesetController(new TTilesetController(this))
  , mCharacterController(new TCharacterPanelController(this))
  , mMapsDockController(new TMapsDockController(this))
  , mLayersController(new TLayersController(this))
  , mAnimationController(new TAnimationController(this))
  , mObjectController(new TObjectController(this))
{
    connect(mTabController, SIGNAL(requestCloseDocument(TDocument*)), this, SLOT(slotRequestCloseDocument(TDocument*)));
    connect(mTabController, SIGNAL(requestSwitchToDocument(TDocument*)), this, SLOT(slotRequestSwitchToDocument(TDocument*)));
    connect(mTabController, SIGNAL(documentDirtyFlagChanged(TDocument*,bool)), this, SLOT(slotDocumentDirtyFlagChanged(TDocument*,bool)));

    connect(mMainPropertyController,
            SIGNAL(propertyItemValueChanged(TPropertyItem*,QVariant)),
            this,
            SLOT(slotPropertyItemValueChanged(TPropertyItem*,QVariant)));
    connect(mMainPropertyController,
            SIGNAL(propertyItemActived(TPropertyItem*)),
            this,
            SLOT(slotPropertyItemActived(TPropertyItem*)));

    connect(mMapsDockController, SIGNAL(requestOpenMap(TMap*)), this, SLOT(slotRequestOpenMap(TMap*)));

    connect(mLayersController, SIGNAL(layerSelected(int)), this, SLOT(slotOnLayerSelected(int)));
    connect(mAnimationController,
            SIGNAL(requestDisplayPropertySheet(TPropertySheet*)),
            this,
            SLOT(slotRequestDisplayPropertySheet(TPropertySheet*)));

    connect(mAnimationController, SIGNAL(requestAdjustFPS(int)), this, SLOT(slotRequestAdjustFPS(int)));
    connect(mAnimationController, SIGNAL(requestPlayAnimation()), this, SLOT(slotRequestPlayAnimation()));
    connect(mAnimationController, SIGNAL(requestStopPlayAnimation()), this, SLOT(slotRequestStopPlayAnimation()));

    connect(TAssetsManager::getInstance(), SIGNAL(onProgress(int,int)), this, SLOT(slotOnResourceLoadProgress(int,int)));
}

TMainController::~TMainController()
{
    TPreferences *preferences = TPreferences::instance();

    // save opened files and properties
    if(mDocument)
        preferences->setLastActiveFile(mDocument->fileName());

    QStringList fileList;
    for(TDocument *document : mCore->documents())
    {
        fileList.append(document->fileName());
    }
    preferences->setRecentOpenedFiles(fileList);
}

bool TMainController::joint(TMainWindow *mainWindow, TCore *core)
{
    Q_ASSERT(mainWindow);
    Q_ASSERT(core);

    TAbstractController::joint(mainWindow, core);

    bool ret = TAbstractController::jointAll(mainWindow, core);
    if(ret)
    {
        connect(mainWindow, SIGNAL(requestOpenMap(QString)), this, SLOT(slotRequestOpenMap(QString)));
        connect(mainWindow, SIGNAL(requestCreateNewMap()), this, SLOT(slotRequestCreateNewMap()));
        connect(mainWindow, SIGNAL(requestSaveCurrentMap()), this, SLOT(slotRequestSaveCurrentMap()));
        connect(mainWindow, SIGNAL(requestSaveAllMaps()), this, SLOT(slotRequestSaveAllMaps()));
        connect(mainWindow, SIGNAL(requestCloseCurrentMap()), this, SLOT(slotRequestCloseCurrentMap()));
        connect(mainWindow, SIGNAL(requestCloseAllMaps()), this, SLOT(slotRequestCloseAllMaps()));
        connect(mainWindow, SIGNAL(requestDisplayMapProperties()), this, SLOT(slotRequestDisplayMapProperties()));
        connect(mainWindow, SIGNAL(requestExitApp(bool&)), this, SLOT(slotRequestExitApp(bool&)));
        connect(mainWindow, SIGNAL(requestRunCurrentMap()), this, SLOT(slotRequestRunCurrentMap()));
        connect(mainWindow, SIGNAL(requestMoveState(bool,bool&)), this, SLOT(slotRequestMoveState(bool,bool&)));
        connect(mainWindow, SIGNAL(requestShowBorder(bool)), this, SLOT(slotRequestShowBorder(bool)));
        connect(mainWindow, SIGNAL(onActionSelectPushed()), this, SLOT(slotOnActionSelectPushed()));
        connect(mainWindow, SIGNAL(onActionInsertPushed()), this, SLOT(slotOnActionInsertPushed()));

        TPreferences *prefs = TPreferences::instance();
        QString gameRoot = prefs->gameRoot();
        QStringList arguments = QCoreApplication::arguments();
        if(arguments.size() > 1)
            gameRoot = arguments.at(1);

        bool success = false;
        do {
            success = core->loadResource(gameRoot);
            if(!success) {
                gameRoot = TSelectRootDialog::getSelectedRoot(mainWindow);
                if(gameRoot.isEmpty())
                    return false;
            }
        } while(!success);
        prefs->setGameRoot(gameRoot);

        QString gameExeFileName = gameRoot + "/mh.exe";
        prefs->setEnginePath(gameExeFileName);

        mainWindow->asShow();
        if(prefs->openLastFile())
        {
            bool showErrorDialog = true;
            for(QString file : prefs->recentOpenedFiles())
            {
                TDocument *document = nullptr;
                try {
                    document = mCore->open(file);
                } catch(QString s) {
                    if(showErrorDialog) {
                        int dialogCode = QMessageBox::critical(mMainWindow,
                                              tr("Error"),
                                              tr("Fail to open file %1:\n\n%2").arg(file).arg(s),
                                              QMessageBox::Ok|QMessageBox::Ignore);
                        if(dialogCode == QMessageBox::Ignore)
                            showErrorDialog = false;
                    }
                    continue;
                } catch(...) {
                    if(showErrorDialog) {
                        int dialogCode = QMessageBox::critical(mMainWindow,
                                          tr("Error"),
                                          tr("Unknown error."),
                                          QMessageBox::Ok|QMessageBox::Ignore);
                        if(dialogCode == QMessageBox::Ignore)
                            showErrorDialog = false;
                    }
                    continue;
                }
                if(document)
                    mTabController->addDocument(document);
            }
            TDocument *document = mCore->find(prefs->lastActiveFile());
            if(document) {
                setCurrentDocument(document);
            }
        }
    }
    return ret;
}

void TMainController::setCurrentDocument(TDocument *document)
{
    if(mDocument == document)
        return;

    mTabController->setCurrentDocument(document);
    mDocument = document;
}

void TMainController::slotRequestOpenMap(const QString &file)
{
    if(!mCore || !mMainWindow || !mTabController)
        return;

    TDocument *document = nullptr;
    try {
        document = mCore->open(file);
    } catch(QString s) {
        QMessageBox::critical(mMainWindow,
                              tr("Error"),
                              tr("Fail to open file %1:\n\n%2").arg(file).arg(s),
                              QMessageBox::Ok);
        return;
    } catch(...) {
        QMessageBox::critical(mMainWindow,
                              tr("Error"),
                              tr("Unknown error."),
                              QMessageBox::Ok);
        return;
    }

    setCurrentDocument(document);
    mMainWindow->addRecentFile(document->fileName());
}

void TMainController::slotRequestCreateNewMap()
{
    if(!mMainWindow)
        return;

    // Set module names to new map dialog
    TNewMapDialog *newMapDialog = mMainWindow->getNewMapDialog();
    if(!newMapDialog)
        return;

    QStringList moduleNames;
    QList<int> advIdList;
    QList<int> vsIdList;
    QList<int> ctfIdList;
    mCore->getModuleNameIds(moduleNames, advIdList, vsIdList, ctfIdList);
    newMapDialog->setModuleNameIds(moduleNames, advIdList, vsIdList, ctfIdList);

    int result = newMapDialog->exec();
    if(result == QDialog::Accepted) {
        QString moduleName = newMapDialog->getModuleName();
        TMap::Type mapType = TMap::stringToType(newMapDialog->getMapTypeName());
        int mapId = newMapDialog->getMapId();
        createNewDocument(moduleName, mapType, mapId);
    }
}

void TMainController::slotRequestSaveCurrentMap()
{
    TDocument *document = (TDocument*)mMainWindow->getTabWidget()->currentDocument();
    if(!document)
        return;

    mCore->saveMap(document);
}

void TMainController::slotRequestSaveAllMaps()
{
    mCore->saveAllMaps();
}

void TMainController::slotRequestCloseDocument(TDocument *document)
{
    if(!document)
        return;

    if(document->isDirty())
    {
        int code = QMessageBox::question(
                    mMainWindow, tr("Question."),
                    tr("The document is not saved, do you want to save it?"),
                    QMessageBox::Save|QMessageBox::No|QMessageBox::Cancel);
        if(code == QMessageBox::Cancel)
            return;
        else if(code == QMessageBox::Save)
        {
            document->save();
        }
    }
    mTabController->removeDocument(document);
    mCore->closeDocument(document);
}

void TMainController::slotRequestSwitchToDocument(TDocument *document)
{
    mUndoController->setCurrentDocument(document);
    mMainPropertyController->setCurrentDocument(document);
    mMiniSceneController->setCurrentDocument(document);
    mLayersController->setCurrentDocument(document);
    mTilesetController->setCurrentDocument(document);
    mAnimationController->setCurrentDocument(document);
    mObjectController->setCurrentDocument(document);

    if(mDocument) {
        mDocument->disconnect(this);
    }
    mDocument = document;

    if(mDocument) {
        connect(mDocument, SIGNAL(dirtyFlagChanged(bool)), this, SLOT(slotOnDirtyFlagChanged(bool)));
        connect(mDocument, SIGNAL(editModeChanged(EditMode,EditMode)), this, SLOT(slotOnEditModeChanged(EditMode,EditMode)));
    }
    mMainWindow->enableSaveAction(document&&document->isDirty());
    mMainWindow->enableRunAction(document!=nullptr);
}

void TMainController::slotDocumentDirtyFlagChanged(TDocument *document, bool isDirty)
{
    Q_UNUSED(document);

    mMainWindow->enableSaveAction(isDirty);
    mMainWindow->enableSaveAllAction(mCore->hasDirtyDocument());
}

void TMainController::slotPropertyItemValueChanged(TPropertyItem *propertyItem, const QVariant &newValue)
{
    if(!propertyItem || !mDocument)
        return;

    TPropertySheet *propertySheet = qobject_cast<TPropertySheet*>(propertyItem->parent());
    if(!propertySheet)
        return;

    TPropertyItems propertyItems;
    propertyItems.append(propertyItem);
    if(propertyItems.size() > 0)
    {
        TPropertyUndoCommand *undoCommand = new TPropertyUndoCommand(
                    propertyItems,
                    propertyItem,
                    newValue);
        mDocument->addUndoCommand(undoCommand);
    }
}

void TMainController::slotPropertyItemActived(TPropertyItem *propertyItem)
{
    if(!propertyItem)
        return;
}

void TMainController::slotOnResourceLoadProgress(int progress, int total)
{
    if(mMainWindow) {
        mMainWindow->getLoadingDialog()->setProgress(progress, total);
    }
}

void TMainController::slotRequestOpenMap(TMap *map)
{
    if(!map)
        return;

    try {
        TDocument *document = mCore->open(map);
        setCurrentDocument(document);
        mMainWindow->addRecentFile(document->fileName());
    } catch(const QString &e) {
        mMainWindow->showExceptionDialog(e);
    }
}

void TMainController::slotOnLayerSelected(int index)
{
    TGraphicsScene *graphicsScene = mDocument->graphicsScene();
    TLayerItem *layerItem = graphicsScene->getLayerItem(index);
    bool enableTileset = layerItem && layerItem->isTileLayer();

    mTilesetController->setTilesetEnabled(enableTileset);
    mCharacterController->setCharacterEnabled(layerItem && layerItem->isFactoryLayer()); //layerItem && layerItem->isFactoryLayer()

    //set model into object dock
    if(layerItem)
        mObjectController->setObjectListViewModel(layerItem->baseModel());

    // Update stamp pixmap if tile layer or factory is slected
    bool isFactoryLayer = layerItem && layerItem->isFactoryLayer();
    if(enableTileset) {
        TPixmapId *pixmapId = mTilesetController->getCurrentTileId();
        graphicsScene->setCurrentStamp(pixmapId);
    } else if(isFactoryLayer) {
        TPixmapId *pixmapId = mCharacterController->getCurrentPixmapId();
        graphicsScene->setCurrentStamp(pixmapId);
    }
}

void TMainController::slotOnDirtyFlagChanged(bool isDirty)
{
    mMainWindow->enableSaveAction(isDirty);
}

void TMainController::slotOnEditModeChanged(const EditMode &current, const EditMode &)
{
    switch (current) {
    case INSERT:
        mMainWindow->checkInsertAction();
        break;
    case DEFAULT:
    default:
        mMainWindow->checkSelectAction();
        break;
    }
}

void TMainController::slotRequestDisplayPropertySheet(TPropertySheet *propertySheet)
{
    mMainPropertyController->setPropertySheet(propertySheet);
}

void TMainController::slotRequestAdjustFPS(int fps)
{
    if(!mDocument)
        return;

    TGraphicsScene *graphicsScene = mDocument->graphicsScene();
    if(!graphicsScene)
        return;
    graphicsScene->setFps(fps);
}

void TMainController::slotRequestPlayAnimation()
{
    if(!mDocument)
        return;

    TGraphicsScene *graphicsScene = mDocument->graphicsScene();
    if(!graphicsScene)
        return;
    graphicsScene->play();
}

void TMainController::slotRequestStopPlayAnimation()
{
    if(!mDocument)
        return;

    TGraphicsScene *graphicsScene = mDocument->graphicsScene();
    if(!graphicsScene)
        return;
    graphicsScene->suspend();
}

bool TMainController::confirmAllSaved()
{
    if(mCore->hasDirtyDocument())
    {
        int code = QMessageBox::question(
                    mMainWindow, tr("Question."),
                    tr("There are unsaved documents, do you want to save them?"),
                    QMessageBox::SaveAll|QMessageBox::No|QMessageBox::Cancel);
        if(code == QMessageBox::Cancel)
            return false;
        else if(code == QMessageBox::SaveAll)
        {
            slotRequestSaveAllMaps();
        }
    }
    return true;
}

void TMainController::createNewDocument(const QString &moduleName, const TMap::Type &mapType, int mapId)
{
    TDocument *document = mCore->newMap(moduleName, mapType, mapId);
    setCurrentDocument(document);
    mMainWindow->addRecentFile(document->fileName());
}

void TMainController::slotRequestExitApp(bool &approved)
{
    if(TPreferences::instance()->saveBeforeExit())
    {
        slotRequestSaveAllMaps();
        approved = true;
    } else {
        approved = confirmAllSaved();
    }
}

void TMainController::slotRequestCloseCurrentMap()
{
    TDocument *document = mTabController->currentDocument();
    slotRequestCloseDocument(document);
}

void TMainController::slotRequestCloseAllMaps()
{
    if(!confirmAllSaved())
        return;

    for(TDocument *d : mCore->documents())
        slotRequestCloseDocument(d);
}

void TMainController::slotRequestReloadCurrentMap()
{

}

void TMainController::slotRequestDisplayMapProperties()
{
    if(!mDocument)
        return;

    mMainPropertyController->setPropertySheet(mDocument->propertySheet());
}

void TMainController::slotRequestRunCurrentMap()
{
    if(!mDocument)
        return;

    if(mDocument->isDirty())
        mDocument->save();

    TPreferences *prefs = TPreferences::instance();
    QString enginePath = prefs->enginePath();
    QString gameRoot = prefs->gameRoot();
    enginePath.append(' ');
    QStringList parameters;
    parameters.append(QString("\"%1\"").arg(mDocument->fileName()));
    if(!QProcess::startDetached(enginePath, parameters, gameRoot))
        QMessageBox::critical(mMainWindow,
                              tr("Error"),
                              tr("Fail to start process with command %1").arg(enginePath),
                              QMessageBox::Ok);
}

void TMainController::slotRequestMoveState(bool isChecked, bool &result)
{
    if(!mDocument)
        return;

    TGraphicsScene *graphicsScene = mDocument->graphicsScene();
    if(!graphicsScene)
        return;
    if(isChecked)
        result = graphicsScene->play();
    else
        result = graphicsScene->suspend();
}

void TMainController::slotRequestShowBorder(bool show)
{
    TTileItem::setShowBorder(show);
    TPreferences::instance()->setDisplayTrayIcon(show);
}

void TMainController::slotOnActionSelectPushed()
{
    if(!mDocument)
        return;

    mDocument->setEditMode(DEFAULT);
}

void TMainController::slotOnActionInsertPushed()
{
    if(!mDocument)
        return;

    TBaseModel::Type currentModelType = mDocument->getSceneModel()->getCurretnModelType();
    if(currentModelType == TBaseModel::TILE) {
        TTileId *tileId = mCore->tilesetModelManager()->getCurrentTileId();
        mDocument->setTileStamp(tileId);
    }
    mDocument->setEditMode(INSERT);
}

void TMainController::slotTimerEvent()
{

}
