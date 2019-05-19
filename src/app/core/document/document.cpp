#include "document.h"
#include "../shared/filesystemwatcher.h"
#include "../assets/assetsmanager.h"
#include "base/tr.h"

#include <QUuid>

static const QString P_NAME = T("Name");

TDocument::TDocument(const QString &file, QObject *parent) :
    TPropertyObject(parent)
  , mIsDirty(false)
  , mUndoStack(new QUndoStack(this))
  , mFileName(file)
  , mFileWatcher(new TFileSystemWatcher(this))
  , mSceneModel(new TSceneModel(this))
  , mGraphicsScene(new TGraphicsScene(this))
  , mEditMode(DEFAULT)
{
    setObjectName("Document");

    connect(mUndoStack, SIGNAL(cleanChanged(bool)), this, SLOT(slotModificationChanged(bool)));
    mUndoStack->setClean();

    connect(mGraphicsScene, SIGNAL(requestUndo()), mUndoStack, SLOT(undo()));
    connect(mGraphicsScene, SIGNAL(requestRedo()), mUndoStack, SLOT(redo()));

    connect(mFileWatcher, SIGNAL(fileChanged(QString)), this, SLOT(slotFileChanged(QString)));
    connect(mFileWatcher, SIGNAL(directoryChanged(QString)), this, SLOT(slotDirectoryChanged(QString)));

    initPropertySheet();

    if(!file.isEmpty())
        load(file);
}

TDocument::~TDocument()
{

}

TDocument *TDocument::create()
{
    TDocument *document = new TDocument;
    return document;
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
            mUndoStack->setClean();
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
    QFileInfo fileInfo(file);
    setFileName(file);
    if(fileInfo.isFile() && fileInfo.exists())
    {
        try {
            QFile f(file);
            QDataStream stream(&f);
            stream.setByteOrder(QDataStream::LittleEndian);
            stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
            f.open(QIODevice::ReadOnly);
            mSceneModel->readFromStream(stream);
            mGraphicsScene->setSceneModel(mSceneModel);
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

void TDocument::setTileStamp(TTileId *tileStamp)
{
    if(!tileStamp)
        return;

    mGraphicsScene->setCurrentTileId(tileStamp);
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
