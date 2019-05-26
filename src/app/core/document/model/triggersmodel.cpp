#include "triggersmodel.h"

TTriggersModel::TTriggersModel(QObject *parent) :
    TBaseModel(TBaseModel::TRIGGER, parent)
{
    setName(tr("TriggerModel"));
}

TTriggersModel::~TTriggersModel()
{

}

void TTriggersModel::clear()
{

}

TTriggerList TTriggersModel::triggerList() const
{
    return mTriggerList;
}

void TTriggersModel::setTriggerList(const TTriggerList &triggerList)
{
    mTriggerList = triggerList;
}

void TTriggersModel::readFromStream(QDataStream &stream)
{
    int triggerAmount;
    stream >> triggerAmount;

    mTriggerList.clear();
    for(int i=0;i<triggerAmount;i++) {
        TTrigger *trigger = new TTrigger(this);
        mTriggerList.append(trigger);
    }
}

void TTriggersModel::saveToStream(QDataStream &stream) const
{
    stream << mTriggerList.size();

    for(TTrigger *trigger : mTriggerList) {
        trigger->saveToStream(stream);
    }
}

int TTriggersModel::rowCount(const QModelIndex &) const
{
    return mTriggerList.size();
}

int TTriggersModel::columnCount(const QModelIndex &parent) const
{
    return TBaseModel::columnCount(parent);
}

QVariant TTriggersModel::data(const QModelIndex &index, int role) const
{
    return TBaseModel::data(index, role);
}
