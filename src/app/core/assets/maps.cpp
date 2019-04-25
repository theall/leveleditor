#include "maps.h"
#include "../document/document.h"

bool idCompare(TMap *map1, TMap *map2)
{
    return map1->id() < map2->id();
}

TMap::TMap(const TMap::Type &type, TMapBundle *parent) :
    QObject(parent)
  , mType(type)
  , mId(-1)
  , mDocument(nullptr)
  , mMapBundle(parent)
  , mIndexInMapBundle(-1)
{

}

TMap::~TMap()
{

}

QString TMap::name() const
{
    return mName;
}

void TMap::setName(const QString &name)
{
    mName = name;
}

QPixmap TMap::thumbnail() const
{
    return mThumbnail;
}

void TMap::setThumbnail(const QPixmap &thumbnail)
{
    mThumbnail = thumbnail;
    emit thumbChanged(thumbnail);
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
    mId = id;
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
    mFileFullPath = fullFilePath;
}

TDocument *TMap::document() const
{
    return mDocument;
}

void TMap::setDocument(TDocument *document)
{
    mDocument = document;
}

TDocument *TMap::open()
{
    if(!mDocument) {
        mDocument = new TDocument(mFileFullPath);
    }
    return mDocument;
}

TMapBundle::TMapBundle(TModule *parent) :
    QObject(parent)
  , mIndexInModule(-1)
  , mHasOpenedMap(false)
  , mHasDirtyMap(false)
  , mModule(parent)
{

}

TMapBundle::~TMapBundle()
{

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

}

int TMapBundle::remove(int index)
{

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

void TMapBundle::sort()
{
    qSort(mMapList.begin(), mMapList.end(), idCompare);
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
        mMapBundleList.at(i)->setIndexInModule(i);
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
