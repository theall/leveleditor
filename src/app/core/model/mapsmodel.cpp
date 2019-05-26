#include "mapsmodel.h"
#include "../assets/pixmap.h"

TMapsModel::TMapsModel(QObject *parent) :
    QAbstractItemModel(parent)
  , mOpenedColor(QColor(Qt::blue))
  , mDirtyColor(QColor(Qt::red))
  , mCurrentModule(nullptr)
{
    mOpenedColor.setAlpha(32);
    mDirtyColor.setAlpha(32);
}

TMapsModel::~TMapsModel()
{

}

TModuleList TMapsModel::moduleList() const
{
    return mModuleList;
}

void TMapsModel::setModuleList(const TModuleList &moduleList)
{
    mModuleList = moduleList;

    for(int i=0;i<mModuleList.size();i++) {
        mModuleList.at(i)->setIndexInModel(i);
    }
}

int TMapsModel::add(TModule *module, int index)
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

int TMapsModel::remove(int index)
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

int TMapsModel::remove(TModule *module)
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

TModule *TMapsModel::currentModule() const
{
    return mCurrentModule;
}

QColor TMapsModel::dirtyColor() const
{
    return mDirtyColor;
}

void TMapsModel::setDirtyColor(const QColor &dirtyColor)
{
    mDirtyColor = dirtyColor;
}

TMap *TMapsModel::find(const QString &mapFilePath) const
{
    TMap *map = nullptr;
    for(TModule *module : mModuleList) {
        map = module->find(mapFilePath);
        if(map)
            break;
    }
    return map;
}

TMap *TMapsModel::find(TDocument *document) const
{
    TMap *map = nullptr;
    for(TModule *module : mModuleList) {
        map = module->find(document);
        if(map)
            break;
    }
    return map;
}

TMap *TMapsModel::createMap(const QString &moduleName, const TMap::Type &mapType, int mapId)
{
    TModule *targetModule = nullptr;
    for(TModule *module : mModuleList) {
        if(module->name() == moduleName) {
            targetModule = module;
            break;
        }
    }
    if(!targetModule)
        return nullptr;

    TMapBundle *mapBundle = targetModule->getMapBundle(mapType);
    if(!mapBundle)
        return nullptr;

    TMap *map = mapBundle->newMap(mapType);
    map->setId(mapId);
    mapBundle->add(map);
    return map;
}

QColor TMapsModel::openedColor() const
{
    return mOpenedColor;
}

void TMapsModel::setOpenedColor(const QColor &openedColor)
{
    mOpenedColor = openedColor;
}

QModelIndex TMapsModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    QObject *data = (QObject*)parent.internalPointer();
    if (!parent.isValid()) {
        // Module list
        TModule *module = mModuleList.at(row);
        if(module)
            return createIndex(row, column, module);
    } else if(TModule *module = dynamic_cast<TModule*>(data)) {
        TMapBundle *mapBundule = module->getMapBundle(TMap::Type(row));
        if(mapBundule)
            return createIndex(row, column, mapBundule);
    }  else if(TMapBundle *mapBundle = dynamic_cast<TMapBundle*>(data)) {
        TMap *map = mapBundle->getMap(row);
        if(map)
            return createIndex(row, column, map);
    }
    return QModelIndex();
}

QModelIndex TMapsModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    QObject *data = (QObject*)index.internalPointer();
    if(TMapBundle *mapBundle = dynamic_cast<TMapBundle*>(data)) {
        if(TModule *module = mapBundle->getModule())
            return createIndex(module->getIndexInModel(), 0, module);
    } else if(TMap *map= dynamic_cast<TMap*>(data)) {
        if(TMapBundle *mapBundle = map->mapBundle())
            return createIndex(mapBundle->getIndexInModule(), 0, mapBundle);
    }
    return QModelIndex();
}

int TMapsModel::rowCount(const QModelIndex &parent) const
{
    QObject *data = (QObject*)parent.internalPointer();
    if(!parent.isValid()) {
        // Root element
        return mModuleList.size();
    } else if(TModule *module = dynamic_cast<TModule*>(data)) {
        return module->size();
    } else if(TMapBundle *mapBundle = dynamic_cast<TMapBundle*>(data)) {
        return mapBundle->size();
    }
    return 0;
}

int TMapsModel::columnCount(const QModelIndex &) const
{
    return 1;
}

QVariant TMapsModel::data(const QModelIndex &index, int role) const
{
    QObject *data = (QObject*)index.internalPointer();
    if(TModule *module = dynamic_cast<TModule*>(data)) {
        if(role == Qt::DisplayRole) {
            return module->name();
        } else if (role == Qt::DecorationRole) {

        } else if(role ==Qt::BackgroundColorRole) {
            if(module->hasOpenedMap()) {
                return mOpenedColor;
            } else if(module->hasDirtyMap()) {
                return mDirtyColor;
            }
        }
    } else if(TMapBundle *mapBundle = dynamic_cast<TMapBundle*>(data)) {
        if(role == Qt::DisplayRole) {
            return mapBundle->name();
        } else if (role == Qt::DecorationRole) {

        } else if(role ==Qt::BackgroundColorRole) {
            if(mapBundle->hasOpenedMap()) {
                return mOpenedColor;
            } else if(mapBundle->hasDirtyMap()) {
                return mDirtyColor;
            }
        }
    } else if(TMap *map = dynamic_cast<TMap*>(data)) {
        if(role == Qt::DisplayRole) {
            if(map->isDirty()) {
                return map->name().append('*');
            } else {
                return map->name();
            }
        } else if(role == Qt::DecorationRole) {
            return map->thumbnailPixmap();
        } else if(role ==Qt::BackgroundColorRole) {
            if(map->isDirty()) {
                return mDirtyColor;
            } else if(map->isOpened()) {
                return mOpenedColor;
            }
        } else if(role == Qt::SizeHintRole) {
            return map->thumbnailPixmap().size();
        }
    }
    return QVariant();
}
