#include "basemodel.h"

TBaseModel::TBaseModel(QObject *parent) :
    QAbstractTableModel(parent)
  , mVisible(true)
  , mLocked(false)
{
    mIcon.addFile(":/scenemodel/images/layer-image.png");
}

QString TBaseModel::name() const
{
    return mName;
}

void TBaseModel::setName(const QString &name)
{
    mName = name;
}

bool TBaseModel::visible() const
{
    return mVisible;
}

void TBaseModel::setVisible(bool visible)
{
    mVisible = visible;
}

QIcon TBaseModel::icon() const
{
    return mIcon;
}

void TBaseModel::setIcon(const QIcon &icon)
{
    mIcon = icon;
}

bool TBaseModel::locked() const
{
    return mLocked;
}

void TBaseModel::setLocked(bool locked)
{
    mLocked = locked;
}

int TBaseModel::columnCount(const QModelIndex &) const
{
    return 3;
}

int TBaseModel::rowCount(const QModelIndex &) const
{
    return 0;
}

QVariant TBaseModel::data(const QModelIndex &, int) const
{
    return QVariant();
}