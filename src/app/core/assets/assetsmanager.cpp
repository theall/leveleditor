#include "assetsmanager.h"
#include "cachedpixmap.h"
#include "cachedsound.h"

#include <QDir>
#include <QFileInfo>
#include <QStringList>

int getThumbId(const QString &mapName) {
    QString idStr;
    for(int i=mapName.size()-1;i>=0;i--) {
        QChar c = mapName.at(i);
        if(!c.isNumber()) {
            break;
        }
        idStr.insert(0, c);
    }
    int id = -1;
    if(!idStr.isEmpty()) {
        id = idStr.toInt();
    }
    return id;
}

QString getThumbName(const QString &mapName) {
    int i = 0;
    int nameLength = mapName.length();
    QString result = mapName;
    for(i=0;i<nameLength;i++) {
        if(mapName.at(i).isNumber()) {
            result.insert(i, '_');
            break;
        }
    }
    int dotIndex = result.indexOf('.');
    if(dotIndex != -1) {
        result.chop(nameLength - dotIndex);
    }
    result.append(".jpg");
    return result;
}

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

bool TAssetsManager::load(const QString &path, bool asynLoad)
{
    if(mPath == path)
        return isValidpath();

    mPath = path;

    if(asynLoad) {
        moveToThread(this);
        start();
    } else {
        run();
    }

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

TFaceList TAssetsManager::getFaceList() const
{
    return mFaceList;
}

TModuleList TAssetsManager::getModuleList() const
{
    return mModuleList;
}

void TAssetsManager::loadAssets()
{    
    // Enumate face list
    FREE_CONTAINER(mFaceList);
    QList<int> faceIdList;
    QStringList faceFileList;
    QString gfxPath = mPath + "/gfx";
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

    // Enumate tile set
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

    // Enumate map thumbnail
    FREE_CONTAINER(mModuleList);
    TPixmapList mapThumbFileList;
    QString mapsPath = mPath + "/Maps";
    QDir mapsDir(mapsPath);
    mapsDir.setFilter(QDir::Dirs);
    QFileInfoList moduleInfoList = mapsDir.entryInfoList(QDir::Dirs|QDir::NoDotAndDotDot);
    for (int i = 0; i < moduleInfoList.size(); i++) {
        QFileInfo moduleFileInfo = moduleInfoList.at(i);
        if(!moduleFileInfo.isDir())
            continue;

        TModule *module = new TModule(this);
        module->setName(moduleFileInfo.baseName());
        TMapBundle *advBundle = module->getAdvBundle();
        TMapBundle *vsBundle = module->getVsBundle();
        TMapBundle *ctfBundle = module->getCtfBundle();

        QDir moduleDir(moduleFileInfo.absoluteFilePath());
        moduleDir.setFilter(QDir::Files | QDir::Hidden);
        QFileInfoList mapFileInfoList = moduleDir.entryInfoList();
        for (int j = 0; j < mapFileInfoList.size(); j++) {
            QFileInfo fileInfo = mapFileInfoList.at(j);
            QString baseName = fileInfo.baseName();
            QString fileName = baseName.toLower();
            QString ext = fileInfo.suffix().toLower();
            if(ext == "dat") {
                if(fileName.at(fileName.size()-1).isNumber()) {
                    TMap *map = nullptr;
                    TMapBundle *mapBundle = nullptr;
                    if(fileName.startsWith("amap")) {
                        map = new TMap(TMap::ADV, advBundle);
                        mapBundle = advBundle;
                    } else if(fileName.startsWith("map")) {
                        map = new TMap(TMap::VS, vsBundle);
                        mapBundle = vsBundle;
                    } else if(fileName.startsWith("ctfmap")) {
                        map = new TMap(TMap::CTF, ctfBundle);
                        mapBundle = ctfBundle;
                    }
                    if(map && mapBundle) {
                        map->setId(getThumbId(baseName));
                        map->setName(baseName);
                        map->setFullFilePath(fileInfo.absoluteFilePath());
                        mapBundle->add(map);

                        TPixmap *thumbnail = map->thumbnail();
                        thumbnail->setFileFullName(moduleDir.absoluteFilePath(getThumbName(baseName)));
                        mapThumbFileList.append(thumbnail);
                    }
                }
            }
        }
        module->sort();
        mModuleList.append(module);
    }

    int assetsLoaded = 0;
    int totalAssets = faceFileList.size() + tileSetIdList.size() + mapThumbFileList.size();
    // real load face bitmap
    for(int i=0;i<faceFileList.size();i++) {
        int faceId = faceIdList.at(i);
        QString faceName = faceFileList.at(i);
        TPixmap *pixmap = new TPixmap(this);
        pixmap->load(faceName);
        if(pixmap->isValid())
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

    // Load map thumbnails
    for(int i=0;i<mapThumbFileList.size();i++) {
        TPixmap *pixmap = mapThumbFileList.at(i);
        pixmap->reload();
        assetsLoaded++;
        if(assetsLoaded%10 == 0)
            emit onProgress(assetsLoaded, totalAssets);
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
