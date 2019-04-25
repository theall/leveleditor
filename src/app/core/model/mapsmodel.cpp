#include "mapsmodel.h"

TMapsModel::TMapsModel(QObject *parent) :
    QAbstractItemModel(parent)
  , mOpenedColor(QColor(Qt::blue))
  , mDirtyColor(QColor(Qt::red))
  , mCurrentModule(nullptr)
{

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

        } else if(role ==Qt::TextColorRole) {
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

        } else if(role ==Qt::TextColorRole) {
            if(mapBundle->hasOpenedMap()) {
                return mOpenedColor;
            } else if(mapBundle->hasDirtyMap()) {
                return mDirtyColor;
            }
        }
    } else if(TMap *map = dynamic_cast<TMap*>(data)) {
        if(role == Qt::DisplayRole) {
            return map->name();
        } else if(role == Qt::DecorationRole) {
            return map->thumbnail();
        } else if(role ==Qt::TextColorRole) {
            if(map->isOpened()) {
                return mOpenedColor;
            } else if(map->isDirty()) {
                return mDirtyColor;
            }
        }
    }
    return QVariant();
}
