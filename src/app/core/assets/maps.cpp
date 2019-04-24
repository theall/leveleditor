#include "maps.h"
#include "../document/document.h"

TMap::TMap(const TMap::Type &type, QObject *parent) :
    QObject(parent)
  , mType(type)
  , mDocument(nullptr)
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

TMapBundle::TMapBundle(QObject *parent) :
    QObject(parent)
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
    }
    emit mapAdded(map, mapIndex);
    return mapIndex;
}

int TMapBundle::remove(TMap *map)
{

}

int TMapBundle::remove(int index)
{

}

TModule::TModule(QObject *parent) :
    QObject(parent)
  , mAdvBundle(new TMapBundle(this))
  , mVsBundle(new TMapBundle(this))
  , mCtfBundle(new TMapBundle(this))
{

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
