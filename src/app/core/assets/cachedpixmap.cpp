#include "cachedpixmap.h"
#include "../shared/filesystemwatcher.h"

#include <QDir>
#include <QFile>
#include <QDebug>

TCachedPixmap::TCachedPixmap(QObject *parent) :
    QThread(parent)
  , mFileWatcher(new TFileSystemWatcher(this))
  , mTerminateFlag(false)
{
    connect(mFileWatcher, SIGNAL(fileChanged(QString)), this, SLOT(slotFileChanged(QString)));
    connect(mFileWatcher, SIGNAL(directoryChanged(QString)), this, SLOT(slotDirectoryChanged(QString)));
}

TCachedPixmap::~TCachedPixmap()
{
    if(isRunning())
    {
        mTerminateFlag = true;
        wait(1000);
    }
}

void TCachedPixmap::setPath(const QString &path)
{
    if(mPath==path)
        return;

    mFileWatcher->removePath(mPath);

    mPath = path;
    mImageDir.setPath(path);

    mFileWatcher->addPath(path);

    mPixmapMap.clear();
    sync();
}


void TCachedPixmap::slotFileChanged(const QString &file)
{
    bool fileRemoved = !QFile::exists(file);
    QString fileBaseName = QFileInfo(file).fileName();
    TPixmap *pixmap = mPixmapMap.value(fileBaseName);
    if(pixmap)
    {
        if(!fileRemoved)
        {
            pixmap->reload();
        } else {
            mPixmapMap.remove(fileBaseName);
        }
        emit updated();
    }
}

void TCachedPixmap::slotDirectoryChanged(const QString &dir)
{
    if(dir==mPath)
    {
        // Load pixmap which is new added
        sync();
    }
}

void TCachedPixmap::run()
{
    qDebug() << "Synchrony pixmap cache.";
    mLock.lock();
    // Remove pixmap which is not exist on disk
    TPixmaps tempList;
    for(TPixmap *pixmap : mPixmapMap.values())
    {
        if(!QFile::exists(pixmap->fileFullName()))
        {
            tempList.append(pixmap);
        }
    }
    for(TPixmap *pixmap : tempList)
    {
        mPixmapMap.remove(pixmap->fileName());
        delete pixmap;
    }

    bool changed = tempList.size() > 0;
    QStringList filters;
    filters << "*.bmp" << "*.png";
    mImageDir.setNameFilters(filters);
    mTerminateFlag = false;
    for(QString imageFile : mImageDir.entryList(QDir::Files))
    {
        if(mTerminateFlag)
            return;

        TPixmap *pixmap = mPixmapMap.value(imageFile);
        if(!pixmap)
        {
            QString fileFullPath = mImageDir.absoluteFilePath(imageFile);
            pixmap = new TPixmap;
            pixmap->load(fileFullPath);
            if(pixmap->pixmap().isNull())
            {
                qDebug() << "Load image failed, " << fileFullPath;
            }
            mPixmapMap.insert(pixmap->fileName(), pixmap);
            mFileWatcher->addPath(fileFullPath);
            changed = true;
        }
    }
    mLock.unlock();

    if(changed)
        emit updated();
    qDebug() << "Synchrony pixmap cache ok";
}

QString TCachedPixmap::getPath() const
{
    return mPath;
}

TPixmaps TCachedPixmap::getPixmapList()
{
    mLock.lock();
    TPixmaps ps = mPixmapMap.values();
    mLock.unlock();
    return ps;
}

bool TCachedPixmap::contains(const QString &file)
{
    return mPixmapMap.value(file)!=nullptr;
}

TPixmap *TCachedPixmap::getPixmap(const QString &file)
{
    mLock.lock();
    TPixmap *p = mPixmapMap.value(file);
    mLock.unlock();
    return p;
}

void TCachedPixmap::sync()
{
    if(!isRunning())
        start();
}
