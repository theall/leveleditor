#include "assetsmanager.h"
#include "cachedpixmap.h"
#include "cachedsound.h"

IMPL_SINGLE_INSTANCE(TAssetsManager)
TAssetsManager::TAssetsManager(QObject *parent) :
    QObject(parent)
  , mCachedPixmaps(new TCachedPixmap(this))
  , mCachedSounds(new TCachedSound(this))
{

}

void TAssetsManager::setPath(const QString &path)
{
    if(mPath==path)
        return;

    mPath = path;
    loadAssets();
}

TPixmap *TAssetsManager::getPixmap(const QString &file) const
{
    return mCachedPixmaps->getPixmap(QFileInfo(file).fileName());
}

TSound *TAssetsManager::getSound(const QString &file) const
{
    return mCachedSounds->getSound(QFileInfo(file).fileName());
}

TCachedPixmap *TAssetsManager::getCachedPixmaps() const
{
    return mCachedPixmaps;
}

TCachedSound *TAssetsManager::getCachedSounds() const
{
    return mCachedSounds;
}

void TAssetsManager::loadAssets()
{

}
