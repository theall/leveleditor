#include "triggermodel.h"

TTriggerModel::TTriggerModel(QObject *parent) :
    TGenericModel<TTrigger>(TBaseModel::TRIGGER, parent)
{
    setName(tr("TriggerModel"));
    setIcon(QIcon(":/scenemodel/images/trigger.png"));
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

int TTriggerModel::rowCount(const QModelIndex &parent) const
{
    if(!parent.isValid()) {
        return mObjectList.size();
    }
    return 0;
}

int TTriggerModel::columnCount(const QModelIndex &) const
{
    return 1;
}

QVariant TTriggerModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row>=0 && row<mObjectList.size())
    {
        if(role==Qt::DisplayRole)
        {
            return tr("Trigger %1").arg(row+1);
        }
    }
    return QVariant();
}

void TTriggerModel::onObjectInserted(const TObjectList &objectList, const QList<int> &indexList)
{
    emit objectInserted(convert(objectList), indexList);
}

void TTriggerModel::onObjectRemoved(const TObjectList &objectList, const QList<int> &indexList)
{
    emit objectRemoved(convert(objectList), indexList);
}
