#include "maps.h"
#include "pixmap.h"
#include "../document/document.h"

#include <QDir>
#include <QSize>
#include <utils/utils.h>

#define IMAGE_SMALL QSize(48,36)
#define IMAGE_LARGE QSize(100,75)

bool idCompare(TMap *map1, TMap *map2)
{
    return map1->id() < map2->id();
}

TMap::TMap(const TMap::Type &type, TMapBundle *parent) :
    QObject(parent)
  , mType(type)
  , mId(-1)
  , mThumbnail(nullptr)
  , mDocument(nullptr)
  , mMapBundle(parent)
  , mIndexInMapBundle(-1)
{
    if(type == ADV) {
        mThumbnail = new TPixmap(QSize(IMAGE_SMALL), this);
    } else {
        mThumbnail = new TPixmap(QSize(IMAGE_LARGE), this);
    }
}

TMap::~TMap()
{

}

QString TMap::name() const
{
    return mName;
}

QString TMap::fileName() const
{
    return mFileName;
}

TPixmap *TMap::thumbnail() const
{
    return mThumbnail;
}

void TMap::setThumbnail(TPixmap *thumbnail)
{
    if(mThumbnail == thumbnail)
        return;

    mThumbnail = thumbnail;

    if(thumbnail)
        emit thumbChanged(thumbnail->content());
}

QPixmap TMap::thumbnailPixmap() const
{
    return mThumbnail?mThumbnail->content():QPixmap();
}

TMap::Type TMap::stringToType(const QString &typeName)
{
    QString lowerTypeName = typeName.toLower();
    if(lowerTypeName == "adv") {
        return TMap::ADV;
    } else if(lowerTypeName == "ctf") {
        return TMap::CTF;
    }
    return TMap::VS;
}

bool TMap::isOpened() const
{
    return mDocument!=nullptr;
}

bool TMap::isDirty() const
{
    if(mDocument)
        return mDocument->isDirty();
    return false;
}

TMap::Type TMap::type() const
{
    return mType;
}

void TMap::setType(const Type &type)
{
    mType = type;
}

int TMap::id() const
{
    return mId;
}

void TMap::setId(int id)
{
    if(mId == id)
        return;

    mId = id;

    QString tpl("map%2");
    QString prefix = "";
    switch (mType) {
    case ADV:
        prefix = "a";
        break;
    case CTF:
        prefix = "CTF";
        break;
    case VS:
    default:
        break;
    }
    if(!prefix.isEmpty())
        tpl.prepend(prefix);
    mName = tpl.arg(mId);

    mFileName = mName + ".dat";
    if(!mFileFullPath.isEmpty()) {
        mFileFullPath = QFileInfo(mFileFullPath).absoluteDir().absoluteFilePath(mName);
    }
}

TMapBundle *TMap::mapBundle() const
{
    return mMapBundle;
}

int TMap::indexInMapBundle() const
{
    return mIndexInMapBundle;
}

void TMap::setIndexInMapBundle(int indexInMapBundle)
{
    mIndexInMapBundle = indexInMapBundle;
}

QString TMap::fullFilePath() const
{
    return mFileFullPath;
}

void TMap::setFullFilePath(const QString &fullFilePath)
{
    if(mFileFullPath == fullFilePath)
        return;

    mFileFullPath = fullFilePath;

    if(mDocument) {
        mDocument->setFileName(mFileFullPath);
    }
    if(mThumbnail) {
        QFileInfo fi(mFileFullPath);
        QString thumbnailFileFullName = fi.absoluteDir().absoluteFilePath(Utils::mapNameToThumbName(fi.baseName()));
        mThumbnail->setFileFullName(thumbnailFileFullName);
    }
}

TDocument *TMap::document() const
{
    return mDocument;
}

TDocument *TMap::createDocument()
{
    if(mDocument)
        delete mDocument;
    mDocument = new TDocument(mType, this);
    if(!mFileFullPath.isEmpty())
        mDocument->setFileName(mFileFullPath);

    updateThumbnail();
    return mDocument;
}

void TMap::setDocument(TDocument *document)
{
    mDocument = document;
}

TDocument *TMap::open()
{
    if(!mDocument) {
        mDocument = new TDocument(mType, mFileFullPath);
    }
    return mDocument;
}

void TMap::close()
{
    if(mDocument) {
        delete mDocument;
        mDocument = nullptr;
    }
}

bool TMap::save()
{
    bool success = false;
    if(mDocument) {
        success = mDocument->save();
        if(success) {
            updateThumbnail();
            mThumbnail->save();
            emit thumbChanged(mThumbnail->content());
        }
    }
    return success;
}

void TMap::updateThumbnail()
{
    QSize imageSize = mType==ADV?IMAGE_SMALL:IMAGE_LARGE;
    QImage image = mDocument->graphicsScene()->toImage(imageSize);
    mThumbnail->setPixmap(QPixmap::fromImage(image));
}

TMapBundle::TMapBundle(TModule *parent) :
    QObject(parent)
  , mIndexInModule(-1)
  , mHasOpenedMap(false)
  , mHasDirtyMap(false)
  , mModule(parent)
  , mSorted(false)
{

}

TMapBundle::~TMapBundle()
{

}

TMap *TMapBundle::newMap(const TMap::Type &mapType)
{
    return new TMap(mapType, this);
}

TMapList TMapBundle::mapList() const
{
    return mMapList;
}

void TMapBundle::setMapList(const TMapList &mapList)
{
    mMapList = mapList;
}

int TMapBundle::add(TMap *map, int index)
{
    if(!map)
        return -1;

    int mapIndex = mMapList.indexOf(map);
    if(mapIndex != -1)
        return mapIndex;

    if(index == -1) {
        mapIndex = mMapList.size();
        mMapList.append(map);
    } else {
        mMapList.insert(index, map);
        mapIndex = index;
        for(int i=mapIndex+1;i<mMapList.size();i++) {
            mMapList.at(i)->setIndexInMapBundle(i);
        }
    }
    map->setIndexInMapBundle(mapIndex);
    emit mapAdded(map, mapIndex);
    return mapIndex;
}

int TMapBundle::remove(TMap *map)
{
    if(!map)
        return -1;

    int mapIndex = mMapList.indexOf(map);
    if(mapIndex == -1)
        return mapIndex;

    mMapList.removeAt(mapIndex);
    emit mapRemoved(map, mapIndex);
    return mapIndex;
}

int TMapBundle::remove(int index)
{
    TMap *map = mMapList.at(index);
    if(!map)
        return -1;

    mMapList.removeAt(index);
    emit mapRemoved(map, index);
    return index;
}

QString TMapBundle::name() const
{
    return mName;
}

void TMapBundle::setName(const QString &name)
{
    mName = name;
}

bool TMapBundle::hasOpenedMap() const
{
    return mHasOpenedMap;
}

bool TMapBundle::hasDirtyMap() const
{
    return mHasDirtyMap;
}

TMap *TMapBundle::getMap(int index) const
{
    if(index>=0 && index<mMapList.size())
        return mMapList.at(index);
    return nullptr;
}

int TMapBundle::getMapIndex(TMap *map) const
{
    return mMapList.indexOf(map);
}

TModule *TMapBundle::getModule() const
{
    return mModule;
}

int TMapBundle::size() const
{
    return mMapList.size();
}

int TMapBundle::getIndexInModule() const
{
    return mIndexInModule;
}

void TMapBundle::setIndexInModule(int indexInModule)
{
    mIndexInModule = indexInModule;
}

int TMapBundle::getNextId()
{
    sort();

    int next = 0;
    if(!mMapList.isEmpty()) {
        next = mMapList.last()->id() + 1;
    }
    return next;
}

void TMapBundle::sort()
{
    if(!mSorted) {
        qSort(mMapList.begin(), mMapList.end(), idCompare);
        mSorted = true;
    }
}

TMap *TMapBundle::find(const QString &mapFilePath) const
{
    for(TMap *map : mMapList) {
        if(map->fullFilePath() == mapFilePath) {
            return map;
        }
    }
    return nullptr;
}

TMap *TMapBundle::find(TDocument *document) const
{
    for(TMap *map : mMapList) {
        if(map->document() == document) {
            return map;
        }
    }
    return nullptr;
}

TMapList TMapBundle::getMapList() const
{
    return mMapList;
}

TModule::TModule(QObject *parent) :
    QObject(parent)
  , mHasOpenedMap(false)
  , mHasDirtyMap(false)
  , mIndexInModel(-1)
  , mAdvBundle(new TMapBundle(this))
  , mVsBundle(new TMapBundle(this))
  , mCtfBundle(new TMapBundle(this))
{
    mAdvBundle->setName(tr("ADV"));
    mVsBundle->setName(tr("VS"));
    mCtfBundle->setName(tr("CTF"));
    mMapBundleList.append(mAdvBundle);
    mMapBundleList.append(mVsBundle);
    mMapBundleList.append(mCtfBundle);
    for(int i=0;i<mMapBundleList.size();i++) {
        TMapBundle *mapBundle = mMapBundleList.at(i);
        mapBundle->setIndexInModule(i);


    }
}

TModule::~TModule()
{

}

QString TModule::name() const
{
    return mName;
}

void TModule::setName(const QString &name)
{
    mName = name;
}

TMapBundle *TModule::getMapBundle(const TMap::Type &type) const
{
    if(type==TMap::ADV)
        return mAdvBundle;
    else if(type==TMap::CTF)
        return mCtfBundle;
    return mVsBundle;
}

TMapBundle *TModule::getAdvBundle() const
{
    return mAdvBundle;
}

TMapBundle *TModule::getVsBundle() const
{
    return mVsBundle;
}

TMapBundle *TModule::getCtfBundle() const
{
    return mCtfBundle;
}

int TModule::size() const
{
    return 3;
}

bool TModule::hasOpenedMap() const
{
    return mHasOpenedMap;
}

bool TModule::hasDirtyMap() const
{
    return mHasDirtyMap;
}

int TModule::getIndexInModel() const
{
    return mIndexInModel;
}

void TModule::setIndexInModel(int indexInModel)
{
    mIndexInModel = indexInModel;
}

void TModule::sort()
{
    for(TMapBundle *mapBundle : mMapBundleList) {
        mapBundle->sort();
    }
}

void TModule::getAvailableIds(int &adv, int &vs, int &ctf) const
{
    adv = mAdvBundle->getNextId();
    vs = mVsBundle->getNextId();
    ctf = mCtfBundle->getNextId();
}

TMap *TModule::find(const QString &mapFilePath) const
{
    TMap *map = nullptr;
    for(TMapBundle *mapBundle : mMapBundleList) {
        map = mapBundle->find(mapFilePath);
        if(map)
            break;
    }
    return map;
}

TMap *TModule::find(TDocument *document) const
{
    TMap *map = nullptr;
    for(TMapBundle *mapBundle : mMapBundleList) {
        map = mapBundle->find(document);
        if(map)
            break;
    }
    return map;
}

TMapBundleList TModule::getMapBundleList() const
{
    return mMapBundleList;
}
