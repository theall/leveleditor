#include "enemyfactorymodel.h"

TEnemyFactoryModel::TEnemyFactoryModel(QObject *parent) :
    TGenericModel<TEnemyFactory>(TBaseModel::ANIMATION, parent)
{
    setName(tr("Factory"));
}

TEnemyFactoryModel::~TEnemyFactoryModel()
{

}

void TEnemyFactoryModel::clear()
{

}

void TEnemyFactoryModel::readFromStream(QDataStream &stream)
{
    int enemyAmount = 0;
    stream >> enemyAmount;
    mObjectList.clear();

    for(int i=0;i<enemyAmount;i++) {
        TEnemyFactory *enemyFactory = new TEnemyFactory(this);
        enemyFactory->readFromStream(stream);
        mObjectList.append(enemyFactory);
    }
}

void TEnemyFactoryModel::saveToStream(QDataStream &stream) const
{
    stream << mObjectList.size();

    for(TEnemyFactory *enemyFactory : mObjectList) {
        enemyFactory->saveToStream(stream);
    }
}

int TEnemyFactoryModel::rowCount(const QModelIndex &) const
{
    return mObjectList.size();
}

int TEnemyFactoryModel::columnCount(const QModelIndex &) const
{
    return 1;
}

QVariant TEnemyFactoryModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row>=0 && row<mObjectList.size())
    {
        if(role==Qt::DisplayRole)
        {
            return tr("Enemy %1").arg(row+1);
        }
    }
    return QVariant();
}

TEnemyFactoryList TEnemyFactoryModel::enemyFactoryList() const
{
    return mObjectList;
}

void TEnemyFactoryModel::setEnemyFactoryList(const TEnemyFactoryList &enemyFactoryList)
{
    mObjectList = enemyFactoryList;
}

void TEnemyFactoryModel::onObjectInserted(const TObjectList &, const QList<int> &indexList)
{
    emit objectInserted(mObjectList, indexList);
}

void TEnemyFactoryModel::onObjectRemoved(const TObjectList &, const QList<int> &indexList)
{
    emit objectRemoved(mObjectList, indexList);
}
