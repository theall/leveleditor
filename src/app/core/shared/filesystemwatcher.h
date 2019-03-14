#ifndef FILESYSTEMWATCHER_H
#define FILESYSTEMWATCHER_H

#include <QMap>
#include <QObject>
#include <QDateTime>
#include <QFileSystemWatcher>

/**
 * A wrapper around QFileSystemWatcher that deals gracefully with files being
 * watched multiple times. It also doesn't start complaining when a file
 * doesn't exist.
 *
 * It's meant to be used as drop-in replacement for QFileSystemWatcher.
 */
class TFileSystemWatcher : public QObject
{
    Q_OBJECT

public:
    explicit TFileSystemWatcher(QObject *parent = nullptr);
    ~TFileSystemWatcher();

    void addPath(const QString &path);
    void removePath(const QString &path);

signals:
    void fileChanged(const QString &path);
    void directoryChanged(const QString &path);

private slots:
    void onFileChanged(const QString &path);
    void onDirectoryChanged(const QString &path);

private:
    int mTimerId;
    QFileSystemWatcher *mWatcher;
    QMap<QString, int> mWatchCount;
    QMap<QString, qint64> mLastChangedPathMap;

    // QObject interface
protected:
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;
};

#endif // FILESYSTEMWATCHER_H
