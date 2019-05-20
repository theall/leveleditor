#include "basemodel.h"

TBaseModel::TBaseModel(TBaseModel::Type type, QObject *parent) :
    QAbstractTableModel(parent)
  , mVisible(true)
  , mLocked(false)
  , mType(type)
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

void TBaseModel::setVisibility(bool visible)
{
    if(mVisible == visible)
        return;

    mVisible = visible;
    emit visibilityChanged(visible);
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
    if(mLocked == locked)
        return;

    mLocked = locked;
    emit lockChanged(locked);
}

TBaseModel::Type TBaseModel::type() const
{
    return mType;
}

void TBaseModel::insertObjects(const TObjectList &objectList, const QList<int> &indexList)
{

}

QList<int> TBaseModel::removeObjects(const TObjectList &objectList)
{

}

bool TBaseModel::isTile() const
{
    return mType == TILE;
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
