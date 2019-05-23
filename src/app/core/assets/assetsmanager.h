#ifndef TASSETSMANAGER_H
#define TASSETSMANAGER_H

#include <QThread>
#include <QPixmap>
#include <utils/macro.h>

#include "sound.h"
#include "pixmap.h"
#include "faceid.h"
#include "tileset.h"
#include "maps.h"

class TCachedSound;
class TCachedPixmap;

class TAssetsManager : public QThread
{
    Q_OBJECT
    DECL_SINGLE_INSTANCE(TAssetsManager)

public:
    TAssetsManager(QObject *parent=Q_NULLPTR);
    ~TAssetsManager();

    bool load(const QString &path, bool asynLoad = true);
    TFaceId *getFace(int id) const;
    TTileId *getTile(int tileSetId, int tileId) const;

    TCachedPixmap *getCachedPixmaps() const;
    TCachedSound *getCachedSounds() const;

    TilesetList getTilesetList() const;

    TFaceList getFaceList() const;

    TModuleList getModuleList() const;

    QString getPath() const;

signals:
    // Notify external object
    void loadCompleted();
    void onProgress(int value, int maxValue);

private:
    QString mPath;
    TFaceList mFaceList;
    TCachedPixmap *mCachedPixmaps;
    TCachedSound *mCachedSounds;
    TilesetList mTilesetList;
    TModuleList mModuleList;

    void loadAssets();
    bool isValidPath() const;

    // QThread interface
protected:
    void run();
};

#endif // TASSETSMANAGER_H
