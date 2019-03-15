#include "assetsmanager.h"
#include "cachedpixmap.h"
#include "cachedsound.h"

#include <QDir>
#include <QFileInfo>
#include <QStringList>

bool tileSetIdCompare(TTileSet *tileSet1, TTileSet *tileSet2)
{
    return tileSet1->id() < tileSet2->id();
}

bool faceIdCompare(TFaceId *face1, TFaceId *face2)
{
    return face1->id() < face2->id();
}

IMPL_SINGLE_INSTANCE(TAssetsManager)
TAssetsManager::TAssetsManager(QObject *parent) :
    QObject(parent)
  , mCachedPixmaps(new TCachedPixmap(this))
  , mCachedSounds(new TCachedSound(this))
  , mCallback(nullptr)
{

}

TAssetsManager::~TAssetsManager()
{
    FREE_CONTAINER(mFaceList);
    FREE_CONTAINER(mTileSetList);
}

void TAssetsManager::load(const QString &path, LoadCallback callback)
{
    if(mPath==path)
        return;

    mPath = path;
    mCallback = callback;

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

TileSetList TAssetsManager::getTileSetList() const
{
    return mTileSetList;
}

void TAssetsManager::loadAssets()
{
    FREE_CONTAINER(mFaceList);

    QList<int> faceIdList;
    QStringList faceFileList;
    QString gfxPath = mPath + "/gfx";
    // Load face list
    QDir gfxDir(gfxPath);
    gfxDir.setFilter(QDir::Dirs);
    QFileInfoList gfxFileInfoList = gfxDir.entryInfoList();
    for (int i = 0; i < gfxFileInfoList.size(); i++) {
        QFileInfo idInfo = gfxFileInfoList.at(i);
        if(!idInfo.isDir())
            continue;

        bool ok = false;
        int id = idInfo.baseName().toInt(&ok);
        if(ok)
        {
            QDir faceDir(idInfo.absoluteFilePath());
            faceDir.setFilter(QDir::Files | QDir::Hidden);
            QFileInfoList faceFileInfoList = faceDir.entryInfoList();
            for (int j = 0; j < faceFileInfoList.size(); j++) {
                QFileInfo fileInfo = faceFileInfoList.at(j);
                QString fileName = fileInfo.baseName().trimmed().toLower();
                if(fileName.startsWith("zwalk0")) {
                    faceIdList.append(id);
                    faceFileList.append(fileInfo.absoluteFilePath());
                    break;
                }
            }
        }
    }

    // Load tile set
    QList<int> tileSetIdList;
    QList<int> tileIdList;
    QStringList tileBitmapList;
    QDir tilesDir = gfxDir.absoluteFilePath("tiles");
    tilesDir.setFilter(QDir::Files | QDir::Hidden);
    QFileInfoList tilesFileInfoList = tilesDir.entryInfoList();
    for (int i = 0; i < tilesFileInfoList.size(); ++i) {
        QFileInfo tileFileInfo = tilesFileInfoList.at(i);
        QString tileName = tileFileInfo.baseName();
        QStringList tileSetNameList = tileName.split("_");
        if(tileSetNameList.size() != 2) // invalid file name
            continue;

        bool ok = false;
        QString tileSetName = tileSetNameList.at(0);
        int tileSetId = tileSetName.toInt(&ok);
        if(!ok)
            continue;

        tileName = tileSetNameList.at(1);
        int tileId = tileName.toInt(&ok);
        if(!ok)
            continue;

        tileSetIdList.append(tileSetId);
        tileIdList.append(tileId);
        tileBitmapList.append(tileFileInfo.absoluteFilePath());
    }

    // real load face bitmap
    for(int i=0;i<faceFileList.size();i++) {
        int faceId = faceIdList.at(i);
        QString faceName = faceFileList.at(i);
        TPixmap *pixmap = new TPixmap(this);
        pixmap->load(faceName);
        if(pixmap)
            mFaceList.append(new TFaceId(faceId, pixmap));
        else
            delete pixmap;
    }
    // Sort
    qSort(mFaceList.begin(), mFaceList.end(), faceIdCompare);


    // Real load tile bitmap
    for(int i=0;i<tileSetIdList.size();i++) {
        TPixmap *pixmap = new TPixmap(this);
        pixmap->load(tileBitmapList.at(i));
        if(!pixmap->isValid()) {
            delete pixmap;
            continue;
        }

        int tileId = tileIdList.at(i);
        int tileSetId = tileSetIdList.at(i);
        TTileSet *targetTileSet = nullptr;
        foreach (TTileSet *tileSet, mTileSetList) {
            if(tileSet->id() == tileSetId) {
                targetTileSet = tileSet;
                break;
            }
        }

        if(targetTileSet == nullptr) {
            targetTileSet = new TTileSet(tileSetId);
            mTileSetList.append(targetTileSet);
        }

        TTileId *tile = new TTileId(tileId, pixmap);
        targetTileSet->add(tile);
        // Sorting
        foreach (TTileSet *tileSet, mTileSetList) {
            tileSet->sort();
        }
        qSort(mTileSetList.begin(), mTileSetList.end(), tileSetIdCompare);
    }
}
