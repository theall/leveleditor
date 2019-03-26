#ifndef TASSETSMANAGER_H
#define TASSETSMANAGER_H

#include <QThread>
#include <QPixmap>
#include <utils/macro.h>

#include "sound.h"
#include "pixmap.h"
#include "faceid.h"
#include "tileset.h"

class TCachedSound;
class TCachedPixmap;

class TAssetsManager : public QThread
{
    Q_OBJECT
    DECL_SINGLE_INSTANCE(TAssetsManager)

public:
    TAssetsManager(QObject *parent=Q_NULLPTR);
    ~TAssetsManager();

    void load(const QString &path);
    TFaceId *getFace(int id) const;
    TTileId *getTile(int tileSetId, int tileId) const;

    TCachedPixmap *getCachedPixmaps() const;
    TCachedSound *getCachedSounds() const;

    TileSetList getTileSetList() const;

signals:
    void onProgress(int value, int maxValue);

private:
    QString mPath;
    TFaceList mFaceList;
    TCachedPixmap *mCachedPixmaps;
    TCachedSound *mCachedSounds;
    TileSetList mTileSetList;
    void loadAssets();

    // QThread interface
protected:
    void run();
};

#endif // TASSETSMANAGER_H
