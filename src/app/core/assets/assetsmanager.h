#ifndef TASSETSMANAGER_H
#define TASSETSMANAGER_H

#include <QObject>
#include <QPixmap>
#include <utils/macro.h>

#include "pixmap.h"
#include "sound.h"

class TCachedSound;
class TCachedPixmap;
class TAssetsManager : public QObject
{
    DECL_SINGLE_INSTANCE(TAssetsManager)

public:
    TAssetsManager(QObject *parent=Q_NULLPTR);

    void setPath(const QString &path);
    TPixmap *getPixmap(const QString &file) const;
    TSound *getSound(const QString &file) const;

    TCachedPixmap *getCachedPixmaps() const;
    TCachedSound *getCachedSounds() const;

private:
    QString mPath;
    TCachedPixmap *mCachedPixmaps;
    TCachedSound *mCachedSounds;
    void loadAssets();
};

#endif // TASSETSMANAGER_H
