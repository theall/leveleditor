#include "maincontroller.h"
#include "../utils/preferences.h"
#include "../gui/dialogs/selectrootdialog.h"
#include "../gui/dialogs/loadingdialog.h"
#include "../gui/component/tabwidget/tabwidget.h"
#include "../core/assets/assetsmanager.h"

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
        connect(mainWindow, SIGNAL(requestOpenProject(QString)), this, SLOT(slotRequestOpenProject(QString)));
        connect(mainWindow, SIGNAL(requestSaveCurrentProject()), this, SLOT(slotRequestSaveCurrentProject()));
        connect(mainWindow, SIGNAL(requestSaveAllProjects()), this, SLOT(slotRequestSaveAllProjects()));
        connect(mainWindow, SIGNAL(requestCloseCurrentProject()), this, SLOT(slotRequestCloseCurrentProject()));
        connect(mainWindow, SIGNAL(requestCloseAllProjects()), this, SLOT(slotRequestCloseAllProjects()));
        connect(mainWindow, SIGNAL(requestDisplayProjectProperties()), this, SLOT(slotRequestDisplayProjectProperties()));
        connect(mainWindow, SIGNAL(requestExitApp(bool&)), this, SLOT(slotRequestExitApp(bool&)));
        connect(mainWindow, SIGNAL(requestRunCurrentProject()), this, SLOT(slotRequestRunCurrentProject()));
        TPreferences *prefs = TPreferences::instance();
        QString gameRoot = prefs->root();
        QStringList arguments = QCoreApplication::arguments();
        if(arguments.size() > 1)
            gameRoot = arguments.at(1);
        bool success = core->loadResource(gameRoot);
        while(!success) {
            gameRoot = TSelectRootDialog::getSelectedRoot(mainWindow);
            if(gameRoot.isEmpty())
                return false;
            success = core->loadResource(gameRoot);
        }
        if(success) {
            prefs->setRoot(gameRoot);
        }
        mainWindow->show();


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

void TMainController::slotRequestOpenProject(const QString &file)
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

void TMainController::slotRequestSaveCurrentProject()
{
    TDocument *document = (TDocument*)mMainWindow->getTabWidget()->currentDocument();
    if(!document)
        return;

    document->save();
}

void TMainController::slotRequestSaveAllProjects()
{
    mCore->saveAllDocuments();
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

    mMainWindow->enableSaveAction(document&&document->isDirty());
    mMainWindow->enableRunAction(document!=nullptr);
    mDocument = document;
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
            slotRequestSaveAllProjects();
        }
    }
    return true;
}

void TMainController::createNewDocument(const QString &projectRoot, const QString &projectName)
{
    TDocument *document = mCore->newDocument(projectRoot, projectName);
    setCurrentDocument(document);
    mMainWindow->addRecentFile(document->fileName());
}

void TMainController::slotRequestExitApp(bool &approved)
{
    if(TPreferences::instance()->saveBeforeExit())
    {
        slotRequestSaveAllProjects();
        approved = true;
    } else {
        approved = confirmAllSaved();
    }
}

void TMainController::slotRequestCloseCurrentProject()
{
    TDocument *document = mTabController->currentDocument();
    slotRequestCloseDocument(document);
}

void TMainController::slotRequestCloseAllProjects()
{
    if(!confirmAllSaved())
        return;

    for(TDocument *d : mCore->documents())
        slotRequestCloseDocument(d);
}

void TMainController::slotRequestReloadCurrentProject()
{

}

void TMainController::slotRequestDisplayProjectProperties()
{
    if(!mDocument)
        return;

    mMainPropertyController->setPropertySheet(mDocument->propertySheet());
}

void TMainController::slotRequestRunCurrentProject()
{
    if(!mDocument)
        return;

    if(mDocument->isDirty())
        mDocument->save();

    QString enginePath = TPreferences::instance()->enginePath();
    enginePath.append(' ');
    QString parameter = QString("\"%1\"").arg(mDocument->fileName());
    enginePath += QDir::toNativeSeparators(parameter);
    if(!QProcess::startDetached(enginePath))
        QMessageBox::critical(mMainWindow,
                              tr("Error"),
                              tr("Fail to start process with command %1").arg(enginePath),
                              QMessageBox::Ok);
}

void TMainController::slotTimerEvent()
{

}
