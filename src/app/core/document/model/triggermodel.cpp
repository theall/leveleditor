#include "triggermodel.h"

TTriggerModel::TTriggerModel(QObject *parent) :
    TGenericModel<TTrigger>(TBaseModel::ANIMATION, parent)
{
    setName(tr("TriggerModel"));
}

TTriggerModel::~TTriggerModel()
{

}

void TTriggerModel::clear()
{

}

TTriggerList TTriggerModel::triggerList() const
{
    return mObjectList;
}

void TTriggerModel::setTriggerList(const TTriggerList &triggerList)
{
    mObjectList = triggerList;
}

void TTriggerModel::readFromStream(QDataStream &stream)
{
    int triggerAmount;
    stream >> triggerAmount;

    mObjectList.clear();
    for(int i=0;i<triggerAmount;i++) {
        TTrigger *trigger = new TTrigger(this);
        trigger->readFromStream(stream);
        mObjectList.append(trigger);
    }
}

void TTriggerModel::saveToStream(QDataStream &stream) const
{
    stream << mObjectList.size();

    for(TTrigger *trigger : mObjectList) {
        trigger->saveToStream(stream);
    }
}

int TTriggerModel::rowCount(const QModelIndex &) const
{
    return mObjectList.size();
}

int TTriggerModel::columnCount(const QModelIndex &parent) const
{
    return TBaseModel::columnCount(parent);
}

QVariant TTriggerModel::data(const QModelIndex &index, int role) const
{
    return TBaseModel::data(index, role);
}

void TTriggerModel::onObjectInserted(const TObjectList &, const QList<int> &indexList)
{
    emit objectInserted(mObjectList, indexList);
}

void TTriggerModel::onObjectRemoved(const TObjectList &, const QList<int> &indexList)
{
    emit objectRemoved(mObjectList, indexList);
}
