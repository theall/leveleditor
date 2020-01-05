#include "assetsmanager.h"
#include "cachedpixmap.h"
#include "cachedsound.h"

#include <QFileInfo>
#include <QStringList>
#include <utils/utils.h>

#include "triggerid.h"

#define GFX_PATH "gfx"
#define MAPS_PATH "maps"
#define TILES_NAME  "tiles"

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

/**
 * @brief Extract stuff type name from file name, for example, "obje1_a1.bmp", return "obj"
 * @param fileName
 * @return QString Object type
 */
QString extractStuffTypeFromFileName(const QString &fileName) {
    // Find index of first digit
    int index = fileName.indexOf(QRegExp("[\\d\\._]"));
    if(index == -1)
        // Invalid file?
        return QString();

    return fileName.left(index);
}

/**
 * @brief Extract sub id from file name, such as "obj12_3.bmp", return 3
 * @param fileName file name
 * @return int
 */
int extractSubIdFromFileName(const QString &fileName) {
    if(fileName.endsWith('_'))
        return -1;

    QStringList splitFileNames = fileName.split("_");
    if(splitFileNames.size() != 2) // invalid file name
        return -1;

    QString idName = splitFileNames.at(1);
    if(idName.at(0) == 'a')
        idName = idName.right(idName.length()-1);
    bool ok = false;
    int id = idName.toInt(&ok);
    if(!ok)
        return -1;
    return id;
}

/**
 * @brief Extract id from filename, such as "obj12_3.bmp", return 2
 * @param fileName file name
 * @return int
 */
int extractIdFromFileName(const QString &fileName) {
    QRegExp rx("[a-zA-Z]+(\\d+)");
    int index = rx.indexIn(fileName);
    if(index == -1)
        return -1;

    int matchedLength = rx.captureCount();
    if(matchedLength < 1)
        return -1;

    QString idName = rx.cap(1);
    bool ok = false;
    int id = idName.toInt(&ok);
    if(!ok)
        return -1;
    return id;
}

bool tileSetIdCompare(TTileset *tileSet1, TTileset *tileSet2)
{
    return tileSet1->id() < tileSet2->id();
}

bool pixmapIdCompare(TPixmapId *id1, TPixmapId *id2)
{
    return id1->id() < id2->id();
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
    clear();
}
// open main Game
bool TAssetsManager::setResourcePath(const QString &path)
{
    mPath = path.trimmed();
    mDir.setPath(mPath);
    mGfxDir.setPath(mDir.absoluteFilePath(GFX_PATH));
    mMapsDir.setPath(mDir.absoluteFilePath(MAPS_PATH));
    bool ret = isValidPath();
    if(!ret)
        mPath.clear();
    return ret;
}

bool TAssetsManager::load(const QString &path, bool asynLoad)
{
    if(!setResourcePath(path))
        return false;

    if(asynLoad) {
        moveToThread(this);
        start();
    } else {
        run();
    }

    return true;
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

QString TAssetsManager::getPath() const
{
    return mPath;
}

QString TAssetsManager::getMapFullName(const QString &module, const QString &mapName) const
{
    QDir moduleDir;
    moduleDir.setPath(mMapsDir.absoluteFilePath(module));
    return moduleDir.absoluteFilePath(mapName);
}

TPixmapId *TAssetsManager::getPixmapId(Category category, int id) const
{
    TPixmapId *pixmapId = nullptr;
    if(category == PLAYER) {
        for(TFaceId *faceId : mFaceList) {
            if(faceId->id() == id) {
                pixmapId = faceId;
                break;
            }
        }
    } else if(category == ITEM) {
        for(TItemId *itemId : mItemIdList) {
            if(itemId->id() == id) {
                pixmapId = itemId;
                break;
            }
        }
    } else if(category == SHOT) {
        for(TShotId *itemId : mShotList) {
            if(itemId->id() == id) {
                pixmapId = itemId;
                break;
            }
        }
    } else if(category == CHUNK) {
        for(TChunkId *itemId : mChunkList) {
            if(itemId->id() == id) {
                pixmapId = itemId;
                break;
            }
        }
    } else if(category == TRIGGER) {
        for(TTriggerId *itemId : mTriggerIdList) {
            if(itemId->id() == id) {
                pixmapId = itemId;
                break;
            }
        }
    }
    return pixmapId;
}

TItemIdList TAssetsManager::getItemIdList() const
{
    return mItemIdList;
}

TShotList TAssetsManager::getShotList() const
{
    return mShotList;
}

TChunkList TAssetsManager::getChunkList() const
{
    return mChunkList;
}

TTriggerIdList TAssetsManager::getTriggerIdList() const
{
    return mTriggerIdList;
}

TTriggerId *TAssetsManager::getTriggerId(int id) const
{
    for(TTriggerId *triggerId : mTriggerIdList) {
        if(triggerId->id() == id)
            return triggerId;
    }
    return nullptr;
}

void TAssetsManager::clear()
{
    FREE_CONTAINER(mFaceList);
    FREE_CONTAINER(mItemIdList);
    FREE_CONTAINER(mShotList);
    FREE_CONTAINER(mChunkList);
    FREE_CONTAINER(mTriggerIdList);
    FREE_CONTAINER(mTilesetList);
}

void TAssetsManager::loadAssets()
{
    clear();

    // Enumate face list
    QList<int> faceIdList;
    QStringList faceFileList;
    mGfxDir.setFilter(QDir::Dirs);
    QFileInfoList gfxFileInfoList = mGfxDir.entryInfoList();
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
                if(fileName != "zwalk0")
                    continue;

                faceIdList.append(id);
                faceFileList.append(fileInfo.absoluteFilePath());
            }
        }
    }

    // Stuff list
    QList<int> stuffIdList;
    QList<int> stuffSubIdList;
    QList<Category> stuffTypeList;
    QStringList stuffBitmapList;
    QDir stuffDir = mGfxDir.absoluteFilePath("stuff");
    stuffDir.setFilter(QDir::Files | QDir::Hidden);
    QFileInfoList stuffFileInfoList = stuffDir.entryInfoList();
    for (int i = 0; i < stuffFileInfoList.size(); ++i) {
        QFileInfo stuffFileInfo = stuffFileInfoList.at(i);
        QString stuffFileName = stuffFileInfo.baseName();// "obj1_a1.bmp"
        // Igore file name end with "_.bmp", example, "obj10_1_.bmp"
        if(stuffFileName.endsWith('_'))
            continue;

        QString stuffTypeName = extractStuffTypeFromFileName(stuffFileName).toLower();
        if(stuffTypeName.isEmpty())
            continue;

        int parentId = extractIdFromFileName(stuffFileName);
        if(parentId == -1)
            continue;

        if(stuffTypeName == "obj") {
            // "obj1_a1.bmp"
            stuffTypeList.append(ITEM);
        } else if(stuffTypeName == "pt") {
            stuffTypeList.append(CHUNK);
        } else if(stuffTypeName == "shot") {
            // "shot38.bmp"
            stuffTypeList.append(SHOT);
        } else if(stuffTypeName == "trig") {
            stuffTypeList.append(TRIGGER);
        } else {
            continue;
        }

        int subId = extractSubIdFromFileName(stuffFileName);
        stuffIdList.append(parentId);
        stuffSubIdList.append(subId);
        stuffBitmapList.append(stuffFileInfo.absoluteFilePath());
    }

    // Enumate tile set
    QList<int> tileSetIdList;
    QList<int> tileIdList;
    QStringList tileBitmapList;
    QDir tilesDir = mGfxDir.absoluteFilePath("tiles");
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
    mMapsDir.setFilter(QDir::Dirs);
    QFileInfoList moduleInfoList = mMapsDir.entryInfoList(QDir::Dirs|QDir::NoDotAndDotDot);
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
            if(ext!="dat" || !fileName.at(fileName.size()-1).isNumber())
                continue;

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
                map->setFullFilePath(fileInfo.absoluteFilePath());
                mapBundle->add(map);

                TPixmap *thumbnail = map->thumbnail();
                thumbnail->setFileFullName(moduleDir.absoluteFilePath(Utils::mapNameToThumbName(baseName)));
                mapThumbFileList.append(thumbnail);
            }
        }
        module->sort();
        mModuleList.append(module);
    }

    int assetsLoaded = 0;
    int totalAssets = faceFileList.size() + tileSetIdList.size() + mapThumbFileList.size() + stuffBitmapList.size();

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
    }

    // Load map thumbnails
    for(int i=0;i<mapThumbFileList.size();i++) {
        TPixmap *pixmap = mapThumbFileList.at(i);
        pixmap->reload();
        assetsLoaded++;
        if(assetsLoaded%10 == 0)
            emit onProgress(assetsLoaded, totalAssets);
    }

    // Load stuff bitmaps
    for(int i=0;i<stuffIdList.size();i++) {
        TPixmap *pixmap = new TPixmap(this);
        pixmap->load(stuffBitmapList.at(i));
        assetsLoaded++;
        if(assetsLoaded%10 == 0)
            emit onProgress(assetsLoaded, totalAssets);
        if(!pixmap->isValid()) {
            delete pixmap;
            continue;
        }

        Category category = stuffTypeList.at(i);
        int stuffId = stuffIdList.at(i);
        int stuffSubId = stuffSubIdList.at(i);
        if(category == ITEM) {
            mItemIdList.append(new TItemId(stuffId, pixmap));
        } else if(category == SHOT) {
            mShotList.append(new TShotId(stuffId, pixmap));
        } else if(category == CHUNK) {
            TChunkId *chunkId = findChunkIdById(stuffId);
            if(chunkId == nullptr) {
                chunkId = new TChunkId(stuffId, pixmap);
                mChunkList.append(chunkId);
            } else {
                chunkId->add(stuffSubId, pixmap);
            }
        } else if(category == TRIGGER) {
            TTriggerId *triggerId = findTriggerIdById(stuffId);
            if(triggerId == nullptr) {
                triggerId = new TTriggerId(stuffId, nullptr, nullptr);
                mTriggerIdList.append(triggerId);
            }
            if(stuffSubId == 1)
                triggerId->setOnPixmap(pixmap);
            else
                triggerId->setOffPixmap(pixmap);
        }
    }

    // Sort
    qSort(mFaceList.begin(), mFaceList.end(), pixmapIdCompare);
    qSort(mShotList.begin(), mShotList.end(), pixmapIdCompare);
    qSort(mTriggerIdList.begin(), mTriggerIdList.end(), pixmapIdCompare);
    qSort(mShotList.begin(), mShotList.end(), pixmapIdCompare);
    qSort(mItemIdList.begin(), mItemIdList.end(), pixmapIdCompare);
    qSort(mChunkList.begin(), mChunkList.end(), pixmapIdCompare);
    qSort(mTilesetList.begin(), mTilesetList.end(), tileSetIdCompare);

    // Sort tile list in tileset
    foreach (TTileset *tileSet, mTilesetList) {
        tileSet->sort();
    }

    // Sort chunk list in chunkid
    for(TChunkId *chunkId : mChunkList) {
        chunkId->sort();
    }

    // Load shot
    emit onProgress(assetsLoaded, totalAssets);
    emit loadCompleted();
}

bool TAssetsManager::isValidPath() const
{
    return !mPath.isEmpty()&&mDir.exists()&&mGfxDir.exists()&&mMapsDir.exists();
}

TTriggerId *TAssetsManager::findTriggerIdById(int id) const
{
    TTriggerId *targetTriggerId = nullptr;
    for(TTriggerId *triggerId : mTriggerIdList) {
        if(triggerId->id() == id) {
            targetTriggerId = triggerId;
            break;
        }
    }
    return targetTriggerId;
}

TChunkId *TAssetsManager::findChunkIdById(int id) const
{
    TChunkId *targetChunkId = nullptr;
    for(TChunkId *chunkId : mChunkList) {
        if(chunkId->id() == id) {
            targetChunkId = chunkId;
            break;
        }
    }
    return targetChunkId;
}

void TAssetsManager::run()
{
    loadAssets();
}
