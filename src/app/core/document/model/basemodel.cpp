#include "basemodel.h"

TBaseModel::TBaseModel(QObject *parent) :
    QAbstractTableModel(parent)
{

}

QString TBaseModel::name() const
{
    return mName;
}

void TBaseModel::setName(const QString &name)
{
    mName = name;
}
