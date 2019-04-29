#include "enemyfactorymodel.h"

TEnemiyFactoryModel::TEnemiyFactoryModel(QObject *parent) :
    QAbstractTableModel(parent)
{

}

TEnemiyFactoryModel::~TEnemiyFactoryModel()
{

}

void TEnemiyFactoryModel::clear()
{

}

void TEnemiyFactoryModel::readFromStream(QDataStream &stream)
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

void TEnemiyFactoryModel::saveToStream(QDataStream &) const
{

}

int TEnemiyFactoryModel::rowCount(const QModelIndex &) const
{
    return mEnemyFactoryList.size();
}

int TEnemiyFactoryModel::columnCount(const QModelIndex &) const
{
    return 1;
}

QVariant TEnemiyFactoryModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row>=0 && row<mEnemyFactoryList.size())
    {
        if(role==Qt::DisplayRole)
        {
            return tr("Enemy %d").arg(row+1);
        }
    }
    return QVariant();
}

TEnemyFactoryList TEnemiyFactoryModel::enemyFactoryList() const
{
    return mEnemyFactoryList;
}

void TEnemiyFactoryModel::setEnemyFactoryList(const TEnemyFactoryList &enemyFactoryList)
{
    mEnemyFactoryList = enemyFactoryList;
}

