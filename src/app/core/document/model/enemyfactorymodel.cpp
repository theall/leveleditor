#include "enemyfactorymodel.h"

TEnemyFactoryModel::TEnemyFactoryModel(QObject *parent) :
    TBaseModel(TBaseModel::INVALID, parent)
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
    mEnemyFactoryList.clear();

    for(int i=0;i<enemyAmount;i++) {
        TEnemyFactory *enemyFactory = new TEnemyFactory(this);
        enemyFactory->readFromStream(stream);
        mEnemyFactoryList.append(enemyFactory);
    }
}

void TEnemyFactoryModel::saveToStream(QDataStream &stream) const
{
    stream << mEnemyFactoryList.size();

    for(TEnemyFactory *enemyFactory : mEnemyFactoryList) {
        enemyFactory->saveToStream(stream);
    }
}

int TEnemyFactoryModel::rowCount(const QModelIndex &) const
{
    return mEnemyFactoryList.size();
}

int TEnemyFactoryModel::columnCount(const QModelIndex &) const
{
    return 1;
}

QVariant TEnemyFactoryModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row>=0 && row<mEnemyFactoryList.size())
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
    return mEnemyFactoryList;
}

void TEnemyFactoryModel::setEnemyFactoryList(const TEnemyFactoryList &enemyFactoryList)
{
    mEnemyFactoryList = enemyFactoryList;
}

IMPL_GENERIC_FUNCTIONS(EnemyFactory)
