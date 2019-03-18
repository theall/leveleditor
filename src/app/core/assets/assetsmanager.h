#ifndef TASSETSMANAGER_H
#define TASSETSMANAGER_H

#include <QObject>
#include <QPixmap>
#include <utils/macro.h>

#include "sound.h"
#include "pixmap.h"
#include "faceid.h"
#include "tileset.h"

class TCachedSound;
class TCachedPixmap;

typedef (*LoadCallback)(int progress, int total);
class TAssetsManager : public QObject
{
    DECL_SINGLE_INSTANCE(TAssetsManager)

public:
    TAssetsManager(QObject *parent=Q_NULLPTR);
    ~TAssetsManager();

    void load(const QString &path, LoadCallback callback = nullptr);
    TFaceId *getFace(int id) const;
    TTileId *getTile(int tileSetId, int tileId) const;

    TCachedPixmap *getCachedPixmaps() const;
    TCachedSound *getCachedSounds() const;

    TileSetList getTileSetList() const;

private:
    QString mPath;
    TFaceList mFaceList;
    TCachedPixmap *mCachedPixmaps;
    TCachedSound *mCachedSounds;
    TileSetList mTileSetList;
    LoadCallback mCallback;
    void loadAssets();
};

#endif // TASSETSMANAGER_H
