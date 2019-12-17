#include "basemodel.h"

TBaseModel::TBaseModel(TBaseModel::Type type, QObject *parent) :
    QAbstractTableModel(parent)
  , mVisible(true)
  , mLocked(false)
  , mType(type)
{
    mIcon.addFile(":/scenemodel/images/layer-image.png");
}

TBaseModel::~TBaseModel()
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

bool TBaseModel::isTile() const
{
    return mType == TILE;
}

void TBaseModel::insertObjects(const TObjectList &objectList, const QList<int> &indexList)
{

}

QList<int> TBaseModel::removeObjects(const TObjectList &objectList)
{

}

QList<int> TBaseModel::moveObjects(const TObjectList &objectList, const QList<int> &indexList)
{
    return QList<int>();
}

void TBaseModel::onObjectInserted(const TObjectList &objectList, const QList<int> &indexList)
{

}

void TBaseModel::onObjectRemoved(const TObjectList &objectList, const QList<int> &indexList)
{

}

//void TBaseModel::onObjectInserted(const TObjectList &, const QList<int> &)
//{
//    emit dataChanged(QModelIndex(), QModelIndex());
//}

//void TBaseModel::onObjectRemoved(const TObjectList &, const QList<int> &)
//{
//    emit dataChanged(QModelIndex(), QModelIndex());
//}

int TBaseModel::columnCount(const QModelIndex &parent) const
{
    return 0;
}

int TBaseModel::rowCount(const QModelIndex &parent) const
{
    return 0;
}

QVariant TBaseModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}
