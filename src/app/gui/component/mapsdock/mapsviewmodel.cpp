#include "mapsviewmodel.h"

TMap::TMap(QObject *parent) :
    QObject(parent)
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

bool TMap::dirty() const
{
    return mDirty;
}

void TMap::setDirty(bool dirty)
{
    if(mDirty == dirty)
        return;

    mDirty = dirty;
    emit dirtyChanged(dirty);
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

TMapBundle *TModule::getMapBundle(const TMapBundle::Type &type) const
{
    if(type==TMapBundle::ADV)
        return mAdvBundle;
    else if(type==TMapBundle::CTF)
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

TMapsViewModel::TMapsViewModel(QObject *parent) :
    QObject(parent)
{

}

TMapsViewModel::~TMapsViewModel()
{

}

TModuleList TMapsViewModel::moduleList() const
{
    return mModuleList;
}

void TMapsViewModel::setModuleList(const TModuleList &moduleList)
{
    mModuleList = moduleList;
}

int TMapsViewModel::add(TModule *module, int index)
{
    if(!module)
        return -1;

    int moduleIndex = mModuleList.indexOf(module);
    if(moduleIndex != -1)
        return moduleIndex;

    if(index == -1)
    {
        moduleIndex = mModuleList.size();
        mModuleList.append(module);
    } else {
        mModuleList.insert(index, module);
        moduleIndex = index;
    }

    emit moduleAdded(module, moduleIndex);
    return moduleIndex;
}

int TMapsViewModel::remove(int index)
{
    if(index<0 || index>=mModuleList.size())
        return -1;

    TModule *module = mModuleList.at(index);
    if(!module)
        return -1;

    mModuleList.removeAt(index);
    emit moduleRemoved(module, index);
    return index;
}

int TMapsViewModel::remove(TModule *module)
{
    if(!module)
        return -1;

    int moduleIndex = mModuleList.indexOf(module);
    if(moduleIndex == -1)
        return -1;

    mModuleList.removeAt(moduleIndex);
    emit moduleRemoved(module, moduleIndex);
    return moduleIndex;
}
