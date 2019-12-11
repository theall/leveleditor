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

void TBaseModel::onObjectInserted(const TObjectList &, const QList<int> &)
{
    emit dataChanged(QModelIndex(), QModelIndex());
}

void TBaseModel::onObjectRemoved(const TObjectList &, const QList<int> &)
{
    emit dataChanged(QModelIndex(), QModelIndex());
}

void TBaseModel::insertObjects(const TObjectList &objectList, const QList<int> &indexList)
{
    Q_UNUSED(objectList);
    Q_UNUSED(indexList);
}

QList<int> TBaseModel::removeObjects(const TObjectList &objectList)
{
    Q_UNUSED(objectList);
    return QList<int>();
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
