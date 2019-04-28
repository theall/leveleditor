#include "enemiesmodel.h"

TEnemiesModel::TEnemiesModel(QObject *parent) :
    QAbstractTableModel(parent)
{

}

TEnemiesModel::~TEnemiesModel()
{

}

void TEnemiesModel::clear()
{

}

void TEnemiesModel::readFromStream(QDataStream &stream)
{
    int enemyAmount = 0;
    stream >> enemyAmount;
    mEnemyList.clear();

    for(int i=0;i<enemyAmount;i++) {
        TEnemy *enemy = new TEnemy(this);
        enemy->readFromStream(stream);
        mEnemyList.append(enemy);
    }
}

void TEnemiesModel::saveToStream(QDataStream &stream) const
{

}

int TEnemiesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mEnemyList.size();
}

int TEnemiesModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant TEnemiesModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row>=0 && row<mEnemyList.size())
    {
        if(role==Qt::DisplayRole)
        {
            return tr("Enemy %d").arg(row+1);
        }
    }
    return QVariant();
}

TEnemyList TEnemiesModel::enemyList() const
{
    return mEnemyList;
}

void TEnemiesModel::setEnemyList(const TEnemyList &enemyList)
{
    mEnemyList = enemyList;
}
