#include "filesystemwatcher.h"

#include <QDebug>
#include <QFile>
#include <QStringList>

TFileSystemWatcher::TFileSystemWatcher(QObject *parent) :
    QObject(parent),
    mWatcher(new QFileSystemWatcher(this))
{
    connect(mWatcher, SIGNAL(fileChanged(QString)),
            SLOT(onFileChanged(QString)));
    connect(mWatcher, SIGNAL(directoryChanged(QString)),
            SLOT(onDirectoryChanged(QString)));

    mTimerId = startTimer(1000);
}

TFileSystemWatcher::~TFileSystemWatcher()
{
    killTimer(mTimerId);
}

void TFileSystemWatcher::addPath(const QString &path)
{
    // Just silently ignore the request when the file doesn't exist
    if (!QFile::exists(path))
        return;

    QMap<QString, int>::iterator entry = mWatchCount.find(path);
    if (entry == mWatchCount.end()) {
        mWatcher->addPath(path);
        mWatchCount.insert(path, 1);
    } else {
        // Path is already being watched, increment watch count
        ++entry.value();
    }
}

void TFileSystemWatcher::removePath(const QString &path)
{
    QMap<QString, int>::iterator entry = mWatchCount.find(path);
    if (entry == mWatchCount.end()) {
        if (QFile::exists(path))
            qWarning() << "FileSystemWatcher: Path was never added:" << path;
        return;
    }

    // Decrement watch count
    --entry.value();

    if (entry.value() == 0) {
        mWatchCount.erase(entry);
        mWatcher->removePath(path);
    }
}

void TFileSystemWatcher::onFileChanged(const QString &path)
{
    // If the file was replaced, the watcher is automatically removed and needs
    // to be re-added to keep watching it for changes. This happens commonly
    // with applications that do atomic saving.
    bool fileRemoved = !QFile::exists(path);
    if (!mWatcher->files().contains(path))
    {
        if (!fileRemoved)
            mWatcher->addPath(path);
    } else {
        if (fileRemoved)
            mWatcher->removePath(path);
    }
    emit fileChanged(path);
}

void TFileSystemWatcher::onDirectoryChanged(const QString &path)
{
    qint64 currentSeconds = QDateTime::currentMSecsSinceEpoch()/1000;
    QMap<QString, qint64>::iterator entry = mLastChangedPathMap.find(path);
    if(entry == mLastChangedPathMap.end()) {
        mLastChangedPathMap.insert(path, currentSeconds);
    } else {
        entry.value() = currentSeconds;
    }
}

void TFileSystemWatcher::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    QString targetPath;
    qint64 currentSeconds = QDateTime::currentMSecsSinceEpoch()/1000;
    QMap<QString, qint64>::Iterator it = mLastChangedPathMap.begin();
    while(it != mLastChangedPathMap.end())
    {
        if(currentSeconds-it.value()>1) {
            targetPath = it.key();
            break;
        }
        ++it;
    }
    if(!targetPath.isEmpty()) {
        mLastChangedPathMap.remove(targetPath);
        emit directoryChanged(targetPath);
    }
}
