#include "tabcontroller.h"
#include "../core/assets/pixmap.h"
#include "../core/shared/filesystemwatcher.h"
#include "../core/document/graphics/graphicsscene.h"
#include "../gui/component/tabwidget/tabwidget.h"
#include "../utils/utils.h"

#include <QDebug>
#include <QMessageBox>

TTabController::TTabController(QObject *parent) :
    TAbstractController(parent)
  , mLastCheckTime(QDateTime::currentDateTime())
  , mLastListCount(0)
  , mLock(false)
{

}

TTabController::~TTabController()
{

}

bool TTabController::joint(TMainWindow *mainWindow, TCore *core)
{
    Q_ASSERT(mainWindow);
    Q_ASSERT(core);

    mTabWidget = mainWindow->getTabWidget();
    Q_ASSERT(mTabWidget);

    connect(mTabWidget, SIGNAL(requestCloseDocument(void*)), this, SLOT(slotRequestCloseDocument(void*)));
    connect(mTabWidget, SIGNAL(requestSwitchToDocument(void*)), this, SLOT(slotRequestSwithToDocument(void*)));
    connect(mTabWidget, SIGNAL(requestExploreFile(QString)), this, SLOT(slotRequestExploreFile(QString)));
    connect(mTabWidget, SIGNAL(requestStartMove(void*)),this,SLOT(slotRequestStartMove(void*)));
    connect(mTabWidget, SIGNAL(requestStopMove(void*)),this,SLOT(slotRequestStopMove(void*)));

    connect(core, SIGNAL(documentFileChanged(QString)), this, SLOT(slotDocumentFileChanged(QString)));

    return TAbstractController::joint(mainWindow, core);
}

void TTabController::setCurrentDocument(TDocument *document)
{
    if(!document || mDocument==document)
        return;

    int index = mTabWidget->findDocumentIndex(document);
    if(index == -1)
    {
        index = addDocument(document);
        mTabWidget->setDocumentDirty(document, document->isDirty());
    } else if(index == mTabWidget->currentIndex()) {
        return;
    }
    mTabWidget->setCurrentIndex(index);
}

void TTabController::removeDocument(TDocument *document)
{
    if(!document)
        return;

    if(mTabWidget->removeTab((void*)document))
    {
        document->disconnect(this);
    }
}

TDocument *TTabController::currentDocument()
{
    return (TDocument*)mTabWidget->currentDocument();
}

TGraphicsScene *TTabController::currentGraphicsScene() const
{
    if(mTabWidget->count() < 1)
        return nullptr;

    return static_cast<TGraphicsScene*>(mTabWidget->currentGraphicsScene());
}

void TTabController::setGraphicsScene(int index, TGraphicsScene *scene)
{
    if(mTabWidget->count() < 1)
        return;

    TGraphicsScene *oldScene = static_cast<TGraphicsScene*>(mTabWidget->currentGraphicsScene());
    if(oldScene && oldScene->isPlaying())
        oldScene->stop();

    mTabWidget->setGraphicsScene(index, scene);
}

void TTabController::play()
{
    if(mTabWidget->count() < 1)
        return;

    TGraphicsScene *scene = static_cast<TGraphicsScene*>(mTabWidget->currentGraphicsScene());
    if(scene)
        scene->play();
}

void TTabController::stop()
{
    if(mTabWidget->count() < 1)
        return;

    TGraphicsScene *scene = static_cast<TGraphicsScene*>(mTabWidget->currentGraphicsScene());
    if(scene)
        scene->stop();
}

int TTabController::addDocument(TDocument *document)
{
    if(!document)
        return -1;

    int index = mTabWidget->addTab(document, document->baseName(), QPixmap());
    mTabWidget->setTabToolTip(index, document->fileName());
    setGraphicsScene(index, document->graphicsScene());

    connect(document, SIGNAL(dirtyFlagChanged(bool)), this, SLOT(slotDocumentDirtyFlagChanged(bool)));
    connect(document, SIGNAL(iconChanged(TPixmap*)), this, SLOT(slotDocumentIconChanged(TPixmap*)));

    return index;
}

void TTabController::slotRequestSwithToDocument(void *document)
{
    emit requestSwitchToDocument((TDocument*)document);
}

void TTabController::slotRequestCloseDocument(void *document)
{
    emit requestCloseDocument((TDocument*)document);
}

void TTabController::slotRequestExploreFile(const QString &file)
{
    Utils::exploreFile(file);
}

void TTabController::slotRequestStartMove(void* document)
{
    TDocument *doc = (TDocument*)document;
    if(!doc)
        return;

    TGraphicsScene *graphicsScene = doc->graphicsScene();
    if(!graphicsScene)
        return;
        graphicsScene->play();
}

void TTabController::slotRequestStopMove(void* document)
{
    TDocument *doc = (TDocument*)document;
    if(!doc)
        return;

    TGraphicsScene *graphicsScene = doc->graphicsScene();
    if(!graphicsScene)
        return;
        graphicsScene->suspend();
}

void TTabController::slotDocumentDirtyFlagChanged(bool isDirty)
{
    TDocument *document = static_cast<TDocument*>(sender());
    if(!document)
        return;
    mTabWidget->setDocumentDirty(document, isDirty);
    emit documentDirtyFlagChanged(document, isDirty);
}

void TTabController::slotDocumentIconChanged(TPixmap *newPixmap)
{
    TDocument *document = static_cast<TDocument*>(sender());
    if(!document)
        return;

    QIcon icon;
    if(newPixmap) {
        icon = QIcon(newPixmap->thumbnail());
    }
    mTabWidget->setDocumentIcon(document, icon);
}

void TTabController::slotDocumentFileChanged(const QString &file)
{
    TDocument *document = mCore->find(file);
    if(!document)
        return;

    QFileInfo fileInfo(file);
    // Ignore file save by ourself
    if(document->lastSaveTime().secsTo(fileInfo.lastModified())<1)
        return;

    if(!mChangedDocuments.contains(document))
        mChangedDocuments.append(document);

    startMyTimer();
}

void TTabController::slotTimerEvent()
{
    if(mLock)
        return;

    QDateTime currentTime = QDateTime::currentDateTime();

    int listCount = mChangedDocuments.count();
    if(listCount < 1)
    {
        mLastCheckTime = currentTime;
        mLastListCount = 0;
        stopMyTimer();
        return;
    }
    if(listCount != mLastListCount)
    {
        mLastListCount = listCount;
        mLastCheckTime = currentTime;
        return;
    } else if(mLastCheckTime.msecsTo(currentTime) < 1000) {
        return;
    }

    mLock = true;
    bool reloadAll = false;
    TDocument *currentDocument = (TDocument*)mTabWidget->currentDocument();
    for(TDocument *d : mChangedDocuments)
    {
        QString fileName = d->fileName();
        if(QFile::exists(fileName))
        {
            if(!reloadAll)
            {
                int code = QMessageBox::question(
                            mMainWindow, tr("Question."),
                            tr("Project file is changed outside editor, do you want to reload it?"),
                            QMessageBox::YesToAll|QMessageBox::Yes|QMessageBox::No|QMessageBox::NoToAll);
                if(code == QMessageBox::NoToAll) {
                    mChangedDocuments.clear();
                    mLock = false;
                    return;
                } else if(code == QMessageBox::No) {
                    continue;
                } else if(code == QMessageBox::YesToAll) {
                    reloadAll = true;
                }
            }
            QString errorString;
            if(currentDocument == d)
            {
                int documentOldIndex = mTabWidget->findDocumentIndex(d);
                emit requestCloseDocument(d);
                try {
                    currentDocument = mCore->open(fileName);
                } catch(QString s) {
                    errorString = tr("Fail to open file %1:\n\n%2").arg(fileName).arg(s);
                } catch(...) {
                    errorString = tr("Unknown error!");
                }
                int documentNewIndex = addDocument(currentDocument);
                mTabWidget->moveTab(documentNewIndex, documentOldIndex);
                mTabWidget->setCurrentIndex(documentOldIndex);
            } else {
                try {
                    d->reload();
                } catch(QString s) {
                    errorString = s;
                } catch(...) {
                    errorString = tr("Unknown error!");
                }
            }
            if(!errorString.isEmpty())
            {
                QMessageBox::critical(mMainWindow, tr("Error"), errorString, QMessageBox::Ok);
                if(!d->isDirty())
                    d->setDirty(true);
            }
        } else {
            if(!d->isDirty())
                d->setDirty(true);
        }
    }
    mChangedDocuments.clear();
    emit requestSwitchToDocument(currentDocument);
    mLock = false;
}
