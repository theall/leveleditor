#include "document.h"
#include "base/tr.h"
#include "undocommand/objectaddcommand.h"

#include "../shared/filesystemwatcher.h"
#include "../assets/assetsmanager.h"
#include "../assets/tileid.h"
#include "../assets/faceid.h"

#ifndef QT_NO_DEBUG
#include <utils/debug.h>
#endif

#include <QUuid>

static const QString P_NAME = T("Name");

TDocument::TDocument(const TMap::Type &mapType, QObject *parent) :
    TPropertyObject(parent)
  , mIsDirty(true)
  , mUndoStack(new QUndoStack(this))
  , mFileWatcher(new TFileSystemWatcher(this))
  , mSceneModel(new TSceneModel(mapType, this))
  , mGraphicsScene(new TGraphicsScene(this))
  , mEditMode(DEFAULT)
{
    setObjectName("Document");
    connetSignalsToSlots();
    initPropertySheet();
    mGraphicsScene->setSceneModel(mSceneModel);
}

TDocument::TDocument(const TMap::Type &mapType, const QString &file, QObject *parent) :
    TPropertyObject(parent)
  , mIsDirty(false)
  , mUndoStack(new QUndoStack(this))
  , mFileWatcher(new TFileSystemWatcher(this))
  , mSceneModel(new TSceneModel(mapType, this))
  , mGraphicsScene(new TGraphicsScene(this))
  , mEditMode(DEFAULT)
{
    setObjectName("Document");
    connetSignalsToSlots();
    initPropertySheet();

    load(file);
    mGraphicsScene->setSceneModel(mSceneModel);
}

TDocument::~TDocument()
{

}

QUndoStack *TDocument::undoStack() const
{
    return mUndoStack;
}

void TDocument::addUndoCommand(QUndoCommand *command)
{
    mUndoStack->push(command);
}

QString TDocument::baseName() const
{
    return mBaseName;
}

bool TDocument::save(const QString &fileName)
{
    if(!fileName.isEmpty())
    {
        setFileName(fileName);
    }
    if(mFileName.isEmpty())
        return false;

    try {
        // Generate data stream first to avoid truncate map file while exception occoured
        QByteArray byteArray;
        QDataStream stream(&byteArray, QIODevice::WriteOnly);
#ifndef QT_NO_DEBUG
        THookBuffer hookBuffer(&byteArray);
        hookBuffer.open(QIODevice::WriteOnly);
        stream.setDevice(&hookBuffer);
#endif
        stream.setByteOrder(QDataStream::LittleEndian);
        stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
        mSceneModel->saveToStream(stream);
        if(!byteArray.isEmpty())
        {
            QFile saveFile(mFileName);
            if (!saveFile.open(QIODevice::WriteOnly)) {
                qWarning("Couldn't open save file.");
                return false;
            }
            saveFile.write(byteArray);
            saveFile.close();

            if(mUndoStack->count() > 0)
                mUndoStack->setClean();
            else
                setDirty(false);
            mLastSaveTime = QFileInfo(mFileName).lastModified();
        }
    } catch(...) {
        return false;
    }

    return true;
}

void TDocument::reload()
{
    load(mFileName);
    mUndoStack->setClean();
}

QString TDocument::fileName() const
{
    return mFileName;
}

void TDocument::setFileName(const QString &fileName)
{
    if(mFileName == fileName)
        return;

    if(!mFileName.isEmpty())
        mFileWatcher->removePath(mFileName);

    QFileInfo fileInfo(fileName);

    mFileName = fileName;
    mBaseName = fileInfo.baseName();

    if(!mFileName.isEmpty())
        mFileWatcher->addPath(mFileName);
}

void TDocument::setBaseName(const QString &baseName)
{
    mBaseName = baseName;
}

TPropertySheet *TDocument::propertySheet() const
{
    return mPropertySheet;
}

void TDocument::load(const QString &file)
{
    if(file.isEmpty())
        return;

    QFileInfo fileInfo(file);
    setFileName(file);
    if(fileInfo.isFile() && fileInfo.exists())
    {
        try {
            QFile f(file);
            f.open(QIODevice::ReadOnly);
            QByteArray byteArray = f.readAll();
            f.close();

            QDataStream stream(byteArray);
#ifndef QT_NO_DEBUG
            THookBuffer hookBuffer(&byteArray);
            hookBuffer.open(QIODevice::ReadOnly);
            stream.setDevice(&hookBuffer);
#endif
            stream.setByteOrder(QDataStream::LittleEndian);
            stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
            mSceneModel->readFromStream(stream);
        } catch (...) {
            throw tr("Load map failed!");
            return;
        }

        mUndoStack->setClean();
        mLastSaveTime = fileInfo.lastModified();
    } else {
        throw tr("File is not exists.");
    }
}

void TDocument::initPropertySheet()
{
    mPropertySheet->addProperty(PT_STRING, P_NAME, PID_NAME, tr("New Map"));
}

void TDocument::connetSignalsToSlots()
{
    connect(mUndoStack, SIGNAL(cleanChanged(bool)), this, SLOT(slotModificationChanged(bool)));
    connect(mUndoStack, SIGNAL(indexChanged(int)), this, SLOT(slotUndoStackIndexChanged(int)));

    connect(mGraphicsScene, SIGNAL(requestUndo()), mUndoStack, SLOT(undo()));
    connect(mGraphicsScene, SIGNAL(requestRedo()), mUndoStack, SLOT(redo()));

    connect(mFileWatcher, SIGNAL(fileChanged(QString)), this, SLOT(slotFileChanged(QString)));
    connect(mFileWatcher, SIGNAL(directoryChanged(QString)), this, SLOT(slotDirectoryChanged(QString)));
}

bool TDocument::isDirty() const
{
    return mIsDirty;
}

void TDocument::setDirty(bool isDirty)
{
    /**
     * Dont't directly set isDirty to mIsDirty, call slotModificationChanged
     * to ensure the signal dirtyFlagChanged is emitted
     */
    slotModificationChanged(!isDirty);
}

void TDocument::slotModificationChanged(bool isClean)
{
    bool dirty = !isClean;
    if(dirty == mIsDirty)
        return;
    mIsDirty = dirty;
    emit dirtyFlagChanged(mIsDirty);
}

void TDocument::slotFileChanged(const QString &file)
{
    bool fileRemoved = !QFile::exists(file);
    if(mFileName==file)
    {
        // Project file changed
        if(fileRemoved)
            setDirty(true);
        else
            emit projectFileChanged();
    }
}

void TDocument::slotDirectoryChanged(const QString &dir)
{
    Q_UNUSED(dir);
}

void TDocument::slotUndoStackIndexChanged(int)
{

}

void TDocument::setTileStamp(TTileId *tileId)
{
    mGraphicsScene->setCurrentStamp(tileId);
}

void TDocument::setFaceStamp(TFaceId *faceId)
{
    mGraphicsScene->setCurrentStamp(faceId);
}

void TDocument::setItemStamp(TItemId *itemId)
{
    mGraphicsScene->setCurrentStamp(itemId);
}

void TDocument::setChunkStamp(TChunkId *ChunkId)
{
    mGraphicsScene->setCurrentStamp(ChunkId);
}

void TDocument::setShotStamp(TShotId *shotId)
{
    mGraphicsScene->setCurrentStamp(shotId);
}

EditMode TDocument::getEditMode() const
{
    return mEditMode;
}

void TDocument::setEditMode(const EditMode &editMode)
{
    if(mEditMode == editMode)
        return;

    EditMode oldMode = mEditMode;
    mEditMode = editMode;
    mGraphicsScene->setEditMode(editMode);

    emit editModeChanged(mEditMode, oldMode);
}

void TDocument::cmdAddObject(const TObject *object, TBaseModel *baseModel)
{
    if(!object || !baseModel) {
        return;
    }
    TObjectList objectList;
    objectList.append(objectList);
    internalAddRemoveObjectCommand(TObjectAddCommand::ADD, baseModel, objectList);
}

void TDocument::cmdAddObject(const TObjectList &objectList, TBaseModel *baseModel)
{
    internalAddRemoveObjectCommand(TObjectAddCommand::ADD, baseModel, objectList);
}

void TDocument::cmdRemoveObject(const TObject *object, TBaseModel *baseModel)
{
    if(!object || !baseModel) {
        return;
    }
    TObjectList objectList;
    objectList.append(objectList);
    internalAddRemoveObjectCommand(TObjectAddCommand::REMOVE, baseModel, objectList);
}

void TDocument::cmdRemoveObject(const TObjectList &objectList, TBaseModel *baseModel)
{
    internalAddRemoveObjectCommand(TObjectAddCommand::REMOVE, baseModel, objectList);
}

void TDocument::internalAddRemoveObjectCommand(TObjectAddCommand::Command id, TBaseModel *baseModel, const TObjectList &objectList)
{
    if(!baseModel)
    {
        return;
    }
    TObjectAddCommand *command = new TObjectAddCommand(
        id,
        baseModel,
        objectList
    );
    addUndoCommand(command);
}

TSceneModel *TDocument::getSceneModel() const
{
    return mSceneModel;
}

QDateTime TDocument::lastSaveTime() const
{
    return mLastSaveTime;
}

TTileId *TDocument::getTileId(int tileSet, int tile)
{
    return TAssetsManager::getInstance()->getTile(tileSet, tile);
}

TGraphicsScene *TDocument::graphicsScene() const
{
    return mGraphicsScene;
}
