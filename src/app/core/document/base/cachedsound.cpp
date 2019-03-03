#include "cachedsound.h"
#include "filesystemwatcher.h"

#include <QDebug>

TCachedSound::TCachedSound(QObject *parent) :
    QThread(parent)
  , mFileWatcher(new TFileSystemWatcher(this))
  , mTerminateFlag(false)
{
    connect(mFileWatcher, SIGNAL(fileChanged(QString)), this, SLOT(slotFileChanged(QString)));
    connect(mFileWatcher, SIGNAL(directoryChanged(QString)), this, SLOT(slotDirectoryChanged(QString)));
}

TCachedSound::~TCachedSound()
{
    if(isRunning())
    {
        mTerminateFlag = true;
        wait(1000);
    }
}

void TCachedSound::setPath(const QString &path)
{
    if(mPath==path)
        return;

    mFileWatcher->removePath(mPath);

    mPath = path;
    mSoundDir.setPath(path);

    mFileWatcher->addPath(path);

    mSoundMap.clear();
    sync();
}


void TCachedSound::slotFileChanged(const QString &file)
{
    bool fileRemoved = !QFile::exists(file);
    TSound *sound = mSoundMap.value(file);
    if(sound)
    {
        if(!fileRemoved)
        {
            sound->reload();
        } else {
            mSoundMap.remove(file);
        }
        emit updated();
    }
}

void TCachedSound::slotDirectoryChanged(const QString &dir)
{
    if(dir==mPath)
    {
        // Load sound which is new added
        sync();
    }
}

void TCachedSound::run()
{
    qDebug() << "Synchrony sound cache.";
    mLock.lock();
    // Remove sound which is not exist on disk
    TSoundList tempList;
    for(TSound *sound : mSoundMap.values())
    {
        if(!QFile::exists(sound->fileFullName()))
        {
            tempList.append(sound);
        }
    }
    for(TSound *sound : tempList)
    {
        mSoundMap.remove(sound->fileName());
        delete sound;
    }

    bool changed = tempList.size() > 0;
    QStringList filters;
    filters << "*.wav" << "*.mp3" << "*.ogg" << "*.flac";
    mSoundDir.setNameFilters(filters);
    mTerminateFlag = false;
    for(QString soundFile : mSoundDir.entryList(QDir::Files))
    {
        if(mTerminateFlag)
            return;

        TSound *sound = mSoundMap.value(soundFile);
        if(!sound)
        {
            QString fileFullPath = mSoundDir.absoluteFilePath(soundFile);
            sound = new TSound;
            sound->load(fileFullPath);
            if(sound->mediaContent()->isNull())
            {
                qDebug() << "Load sound failed, " << fileFullPath;
            }
            mSoundMap.insert(sound->fileName(), sound);
            mFileWatcher->addPath(fileFullPath);
            changed = true;
        }
    }
    mLock.unlock();

    if(changed)
        emit updated();
    qDebug() << "Synchrony sound cache ok";
}

QString TCachedSound::getPath() const
{
    return mPath;
}

TSoundList TCachedSound::getSoundList()
{
    mLock.lock();
    TSoundList ps = mSoundMap.values();
    mLock.unlock();
    return ps;
}

bool TCachedSound::contains(const QString &file)
{
    return mSoundMap.value(file)!=nullptr;
}

TSound *TCachedSound::getSound(const QString &file)
{
    mLock.lock();
    TSound *p = mSoundMap.value(file);
    mLock.unlock();
    return p;
}

void TCachedSound::sync()
{
    if(!isRunning())
        start();
}
