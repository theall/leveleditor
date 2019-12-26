#include "enemymodel.h"
#include "entity/enemyfactory.h"

TEnemyModel::TEnemyModel(QObject *parent) :
    TGenericModel<TEnemy>(TBaseModel::ANIMATION, parent)
  , mEnemyFactory(nullptr)
{
    setName("EnemyModle");
}

TEnemyFactory *TEnemyModel::enemyFactory() const
{
    return mEnemyFactory;
}

void TEnemyModel::setEnemyFactory(TEnemyFactory *enemyFactory)
{
    mEnemyFactory = enemyFactory;
}

void TEnemyModel::saveToStream(QDataStream &stream) const
{
    mEnemyFactory->setEnemyList(mObjectList);
    mEnemyFactory->saveToStream(stream);
}

void TEnemyModel::readFromStream(QDataStream &stream)
{
    if(mEnemyFactory != nullptr) {
        delete mEnemyFactory;
        mEnemyFactory = nullptr;
    }
    mEnemyFactory = new TEnemyFactory(QObject::parent());
    mEnemyFactory->readFromStream(stream);
    mObjectList = mEnemyFactory->enemyList();
}

int TEnemyModel::rowCount(const QModelIndex &) const
{
    return mObjectList.size();
}

int TEnemyModel::columnCount(const QModelIndex &) const
{
    return 1;
}

QVariant TEnemyModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row<0 || row>=mObjectList.size())
        return QVariant();

    TEnemy *enemy = mObjectList.at(row);
    if(role == Qt::DisplayRole) {
        return tr("Enemy %1").arg(row+1);
    } else if(role == Qt::DecorationRole) {
        return enemy->getPixmap()->content();
    }
    return QVariant();
}
