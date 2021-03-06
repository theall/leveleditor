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

TEnemy *TEnemyModel::createEnemy(TFaceId *faceId, const QPointF &pos)
{
    TEnemy *enemy = new TEnemy(this);
    enemy->setPixmapId(faceId);
    enemy->setPos(pos);
    return enemy;
}

TEnemy *TEnemyModel::createEnemy()
{
    return new TEnemy(this);
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
    } /*else if(role == Qt::DecorationRole) {
        return enemy->getPixmap()->content();
    }*/
    return QVariant();
}

void TEnemyModel::onObjectInserted(const TObjectList &objectList, const QList<int> &indexList)
{
    mEnemyFactory->setEnemyList(mObjectList);
    emit objectInserted(convert(objectList), indexList);
}

void TEnemyModel::onObjectRemoved(const TObjectList &objectList, const QList<int> &indexList)
{
    mEnemyFactory->setEnemyList(mObjectList);
    emit objectRemoved(convert(objectList), indexList);
}
