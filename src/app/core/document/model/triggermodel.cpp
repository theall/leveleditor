#include "triggermodel.h"

TTriggerModel::TTriggerModel(QObject *parent) :
    TBaseModel(TBaseModel::TRIGGER, parent)
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
    return mTriggerList;
}

void TTriggerModel::setTriggerList(const TTriggerList &triggerList)
{
    mTriggerList = triggerList;
}

void TTriggerModel::readFromStream(QDataStream &stream)
{
    int triggerAmount;
    stream >> triggerAmount;

    mTriggerList.clear();
    for(int i=0;i<triggerAmount;i++) {
        TTrigger *trigger = new TTrigger(this);
        mTriggerList.append(trigger);
    }
}

void TTriggerModel::saveToStream(QDataStream &stream) const
{
    stream << mTriggerList.size();

    for(TTrigger *trigger : mTriggerList) {
        trigger->saveToStream(stream);
    }
}

int TTriggerModel::rowCount(const QModelIndex &) const
{
    return mTriggerList.size();
}

int TTriggerModel::columnCount(const QModelIndex &parent) const
{
    return TBaseModel::columnCount(parent);
}

QVariant TTriggerModel::data(const QModelIndex &index, int role) const
{
    return TBaseModel::data(index, role);
}

IMPL_GENERIC_FUNCTIONS(Trigger)
