#ifndef CACHEDPIXMAP_H
#define CACHEDPIXMAP_H

#include <QDir>
#include <QMap>
#include <QMutex>
#include <QThread>

#include "pixmap.h"
#include <utils/macro.h>

class TFileSystemWatcher;
class TCachedPixmap : public QThread
{
    Q_OBJECT

public:
    TCachedPixmap(QObject *parent = nullptr);
    ~TCachedPixmap();

    void setPath(const QString &path);
    TPixmap *getPixmap(const QString &file);
    void sync();

    TPixmapList getPixmapList();

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
    QDir mImageDir;
    TFileSystemWatcher *mFileWatcher;
    bool mTerminateFlag;
    QMutex mLock;
    QMap<QString, TPixmap *> mPixmapMap;

    bool contains(const QString &file);
};

#endif // CACHEDPIXMAP_H
