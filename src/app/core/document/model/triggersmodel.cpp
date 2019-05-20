#include "triggersmodel.h"

TTriggersModel::TTriggersModel(QObject *parent) :
    TBaseModel(TBaseModel::TRIGGER, parent)
{
    setName(tr("Trigger"));
}

void TTriggersModel::clear()
{

}

void TTriggersModel::readFromStream(QDataStream &stream)
{

}

void TTriggersModel::saveToStream(QDataStream &stream) const
{

}

int TTriggersModel::rowCount(const QModelIndex &parent) const
{

}

int TTriggersModel::columnCount(const QModelIndex &parent) const
{

}

QVariant TTriggersModel::data(const QModelIndex &index, int role) const
{

}
