#include "mapsmodel.h"

TMapsModel::TMapsModel(QObject *parent) :
    QObject(parent)
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
