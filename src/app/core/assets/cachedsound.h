#ifndef CACHEDSOUND_H
#define CACHEDSOUND_H

#include <QDir>
#include <QMutex>
#include <QThread>
#include "sound.h"

class TFileSystemWatcher;

class TCachedSound : public QThread
{
    Q_OBJECT

public:
    TCachedSound(QObject *parent = nullptr);
    ~TCachedSound();

    void setPath(const QString &path);
    TSound *getSound(const QString &file);
    void sync();

    TSoundList getSoundList();

    QString getPath() const;

signals:
    void updated();

private slots:
    void slotFileChanged(const QString &file);
    void slotDirectoryChanged(const QString &dir);

protected:
    void run() Q_DECL_OVERRIDE;

private:
    QString mPath;
    QDir mSoundDir;
    TFileSystemWatcher *mFileWatcher;
    bool mTerminateFlag;
    QMutex mLock;
    QMap<QString, TSound *> mSoundMap;

    bool contains(const QString &file);
};

#endif // CACHEDSOUND_H
