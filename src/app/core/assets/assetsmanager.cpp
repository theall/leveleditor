#include "assetsmanager.h"
#include "cachedpixmap.h"
#include "cachedsound.h"

#include <QDir>
#include <QFileInfo>
#include <QStringList>

bool tileSetIdCompare(TTileset *tileSet1, TTileset *tileSet2)
{
    return tileSet1->id() < tileSet2->id();
}

bool faceIdCompare(TFaceId *face1, TFaceId *face2)
{
    return face1->id() < face2->id();
}

IMPL_SINGLE_INSTANCE(TAssetsManager)
TAssetsManager::TAssetsManager(QObject *parent) :
    QThread(parent)
  , mCachedPixmaps(new TCachedPixmap(this))
  , mCachedSounds(new TCachedSound(this))
{

}

TAssetsManager::~TAssetsManager()
{
    FREE_CONTAINER(mFaceList);
    FREE_CONTAINER(mTilesetList);
}

bool TAssetsManager::load(const QString &path)
{
    if(mPath == path)
        return isValidpath();

    mPath = path;

    moveToThread(this);
    start();
    return isValidpath();
}

TFaceId *TAssetsManager::getFace(int id) const
{
    foreach (TFaceId *face, mFaceList) {
        if(face->id() == id)
            return face;
    }
    return nullptr;
}

TTileId *TAssetsManager::getTile(int tileSetId, int tileId) const
{
    foreach (TTileset *tileSet, mTilesetList) {
        if(tileSet->id() == tileSetId) {
            foreach (TTileId *tile, tileSet->tileList()) {
                if(tile->id() == tileId)
                    return tile;
            }
        }
    }
    return nullptr;
}

TCachedPixmap *TAssetsManager::getCachedPixmaps() const
{
    return mCachedPixmaps;
}

TCachedSound *TAssetsManager::getCachedSounds() const
{
    return mCachedSounds;
}

TilesetList TAssetsManager::getTilesetList() const
{
    return mTilesetList;
}

TTilesetModelList TAssetsManager::getTilesetModelList() const
{
    return mTilesetModelList;
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

    int assetsLoaded = 0;
    int totalAssets = faceFileList.size() + tileSetIdList.size();
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
        assetsLoaded++;
        if(assetsLoaded%10 == 0)
            emit onProgress(assetsLoaded, totalAssets);
    }
    // Sort
    qSort(mFaceList.begin(), mFaceList.end(), faceIdCompare);


    // Real load tile bitmap
    for(int i=0;i<tileSetIdList.size();i++) {
        TPixmap *pixmap = new TPixmap(this);
        pixmap->load(tileBitmapList.at(i));
        assetsLoaded++;
        if(assetsLoaded%10 == 0)
            emit onProgress(assetsLoaded, totalAssets);
        if(!pixmap->isValid()) {
            delete pixmap;
            continue;
        }

        int tileId = tileIdList.at(i);
        int tileSetId = tileSetIdList.at(i);
        TTileset *targetTileset = nullptr;
        foreach (TTileset *tileSet, mTilesetList) {
            if(tileSet->id() == tileSetId) {
                targetTileset = tileSet;
                break;
            }
        }

        if(targetTileset == nullptr) {
            targetTileset = new TTileset(tileSetId);
            mTilesetList.append(targetTileset);
        }

        TTileId *tile = new TTileId(tileId, pixmap);
        targetTileset->add(tile);
        // Sorting
        foreach (TTileset *tileSet, mTilesetList) {
            tileSet->sort();
        }
        qSort(mTilesetList.begin(), mTilesetList.end(), tileSetIdCompare);
    }

    // Create tileset models
    FREE_CONTAINER(mTilesetModelList);
    for(TTileset *tileset : mTilesetList) {
        TTilesetModel *tilesetModel = new TTilesetModel(tileset, this);
        mTilesetModelList.append(tilesetModel);
    }
    emit onProgress(assetsLoaded, totalAssets);
    emit loadCompleted();
}

bool TAssetsManager::isValidpath() const
{
    QString path = mPath.trimmed();
    if(path.isEmpty())
        return false;
    QDir dir(path);
    if(!dir.exists())
        return false;

    if(!dir.cd("gfx"))
        return false;

    return true;
}

void TAssetsManager::run()
{
    loadAssets();
}
