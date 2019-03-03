#include "document.h"
#include "base/filesystemwatcher.h"
#include "base/cachedpixmap.h"
#include "base/cachedsound.h"
#include "undocommand/layersundocommand.h"

#include <QUuid>

static const char *P_NAME = "Name";

static const char *ATTR_ENUMNAMES = "enumNames";
static const char *RES_PATH_IMAGE = "image";
static const char *RES_PATH_SOUND = "sound";

TDocument::TDocument(const QString &file, QObject *parent) :
    TPropertyObject(parent)
  , mIsDirty(false)
  , mUndoStack(new QUndoStack(this))
  , mFileName(file)
  , mFileWatcher(new TFileSystemWatcher(this))
  , mCachedPixmaps(new TCachedPixmap(this))
  , mCachedSounds(new TCachedSound(this))
  , mSceneModel(new TSceneModel(this))
{
    setObjectName("Document");

    connect(mUndoStack, SIGNAL(cleanChanged(bool)), this, SLOT(slotModificationChanged(bool)));
    mUndoStack->setClean();

    connect(mFileWatcher, SIGNAL(fileChanged(QString)), this, SLOT(slotFileChanged(QString)));
    connect(mFileWatcher, SIGNAL(directoryChanged(QString)), this, SLOT(slotDirectoryChanged(QString)));

    initPropertySheet();

    if(!file.isEmpty())
        load(file);
}

TDocument::~TDocument()
{

}

TDocument *TDocument::create(const QString &projectRoot, const QString &projectName)
{
    TDocument *document = new TDocument;
    QFileInfo fi(projectRoot);
    if(!fi.isDir() || !fi.exists())
    {
        QDir d = fi.absoluteDir();
        d.mkdir(fi.baseName());
    }
    document->setProjectRoot(projectRoot);
    document->setProjectName(projectName);

    QString fillFullName = projectRoot + "/" + projectName + ".json";

    document->save(fillFullName);

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

void TDocument::cmdAddLayer(const QString &name)
{
    TLayer *layer = new TLayer(name, this);
    TLayersUndoCommand *command = new TLayersUndoCommand(
                LUC_ADD,
                mSceneModel->layersModel(),
                layer);
    mUndoStack->push(command);
}

void TDocument::cmdRemoveLayer(TLayer *layer)
{
    if(!layer)
        return;

    TLayersUndoCommand *command = new TLayersUndoCommand(
                LUC_REMOVE,
                mSceneModel->layersModel(),
                layer);
    mUndoStack->push(command);
}

void TDocument::cmdRemoveLayer(int layerIndex)
{
    TLayer *layer = mSceneModel->layersModel()->getLayer(layerIndex);
    if(!layer)
        return;
    cmdRemoveLayer(layer);
}

TPixmap *TDocument::getPixmap(const QString &file) const
{
    return mCachedPixmaps->getPixmap(QFileInfo(file).fileName());
}

QString TDocument::getPixmapRelativePath(const QString &file) const
{
    QString path;
    TPixmap *pixmap = mCachedPixmaps->getPixmap(file);
    if(!pixmap)
        return path;

    path = pixmap->fileFullName();
    return path.right(path.size() - mProjectRoot.size());
}

TSound *TDocument::getSound(const QString &file) const
{
    return mCachedSounds->getSound(QFileInfo(file).fileName());
}

QString TDocument::getSoundRelativePath(const QString &file) const
{
    QString path;
    TSound *sound = mCachedSounds->getSound(file);
    if(!sound)
        return path;

    path = sound->fileFullName();
    return path.right(path.size() - mProjectRoot.size());
}

QString TDocument::baseName() const
{
    return mBaseName;
}

QDir TDocument::projectDir() const
{
    return mProjectDir;
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
    setProjectRoot(fileInfo.absolutePath());

    mFileName = fileName;
    mBaseName = fileInfo.baseName();
    mProjectName = mBaseName;

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

QString TDocument::projectRoot() const
{
    return mProjectRoot;
}

void TDocument::setProjectRoot(const QString &projectRoot)
{
    mProjectDir.setPath(projectRoot);
    mSoundDir.setPath(mProjectDir.absoluteFilePath(RES_PATH_SOUND));

    if(!mProjectDir.exists(RES_PATH_IMAGE))
        mProjectDir.mkdir(RES_PATH_IMAGE);
    if(!mSoundDir.exists())
        mProjectDir.mkdir(RES_PATH_SOUND);

    mProjectRoot = projectRoot;

    // Load image
    mCachedPixmaps->setPath(mProjectDir.absoluteFilePath(RES_PATH_IMAGE));
    // Load sound
    mCachedSounds->setPath(mProjectDir.absoluteFilePath(RES_PATH_SOUND));
}

QString TDocument::projectName() const
{
    return mProjectName;
}

void TDocument::setProjectName(const QString &projectName)
{
    mProjectName = projectName;
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
            f.open(QIODevice::ReadOnly);
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
    mPropertySheet->addProperty(PT_STRING, P_NAME, PID_NAME, tr("New Scene"));
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

void TDocument::slotIconPropertyItemChanged(const QVariant &oldValue)
{
    Q_UNUSED(oldValue);

    TPropertyItem *propertyItem = static_cast<TPropertyItem*>(sender());
    if(!propertyItem)
        return;

    QString newPixmapFile = propertyItem->value().toString();
    emit iconChanged(getPixmap(newPixmapFile));
}

QPixmap TDocument::getIcon() const
{
    return mIcon;
}

void TDocument::setIcon(const QPixmap &icon)
{
    mIcon = icon;
}

TCachedPixmap *TDocument::getCachedPixmaps() const
{
    return mCachedPixmaps;
}

TCachedSound *TDocument::getCachedSounds() const
{
    return mCachedSounds;
}

QDateTime TDocument::lastSaveTime() const
{
    return mLastSaveTime;
}

TGraphicsScene *TDocument::graphicsScene() const
{
    return mSceneModel->graphicsScene();
}
