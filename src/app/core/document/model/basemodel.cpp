#include "basemodel.h"

TBaseModel::TBaseModel(TBaseModel::Type type, QObject *parent) :
    QAbstractItemModel(parent)
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

bool TBaseModel::currentObjectWhetherCurrentModel(TObject::Type type)
{
    if(type == TObject::TILE && mType == TBaseModel::TILE) {
        return true;
    } else if(type == TObject::ANIMATION && mType == TBaseModel::TILE) {
        return true;
    } else if(type == TObject::AREA && mType == TBaseModel::AREA) {
        return true;
    } else if(type == TObject::BOX && mType == TBaseModel::BOX) {
        return true;
    } else if(type == TObject::DAREA && mType == TBaseModel::DAREA) {
        return true;
    } else if(type == TObject::ENEMY && mType == TBaseModel::ENEMY_FACTORY) {
        return true;
    } else if(type == TObject::PLAT && mType == TBaseModel::PLAT) {
        return true;
    }
    return false;
}

bool TBaseModel::isTile() const
{
    return mType == TILE;
}

void TBaseModel::insertObjects(const TObjectList &, const QList<int> &)
{

}

QList<int> TBaseModel::removeObjects(const TObjectList &)
{
    return QList<int>();
}

QList<int> TBaseModel::moveObjects(const TObjectList &, const QList<int> &)
{
    return QList<int>();
}

void TBaseModel::onObjectInserted(const TObjectList &, const QList<int> &)
{

}

void TBaseModel::onObjectRemoved(const TObjectList &, const QList<int> &)
{

}

int TBaseModel::columnCount(const QModelIndex &) const
{
    Q_ASSERT(false);
    return 0;
}

int TBaseModel::rowCount(const QModelIndex &) const
{
    Q_ASSERT(false);
    return 0;
}

QVariant TBaseModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

QModelIndex TBaseModel::index(int row, int column, const QModelIndex &) const
{
    return createIndex(row, column, nullptr);
}

QModelIndex TBaseModel::parent(const QModelIndex &) const
{
    return QModelIndex();
}

void TBaseModel::saveToStream(QDataStream &stream) const
{

}

void TBaseModel::readFromStream(QDataStream &stream)
{

}
