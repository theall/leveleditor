#include "enemyfactorymodel.h"
#include "enemymodel.h"

TEnemyFactoryModel::TEnemyFactoryModel(QObject *parent) :
    TGenericModel<TEnemyFactory>(TBaseModel::ENEMY_FACTORY, parent)
{
    setName(tr("Factory"));
}

TEnemyFactoryModel::~TEnemyFactoryModel()
{

}

void TEnemyFactoryModel::clear()
{
    mObjectList.clear();
    mEnemyModelList.clear();
}

void TEnemyFactoryModel::readFromStream(QDataStream &stream)
{
    int enemyAmount = 0;
    stream >> enemyAmount;

    clear();

    for(int i=0;i<enemyAmount;i++) {
        TEnemyModel *enemyModel = new TEnemyModel(this);
        enemyModel->readFromStream(stream);
        mEnemyModelList.append(enemyModel);
        mObjectList.append(enemyModel->enemyFactory());
    }
}

void TEnemyFactoryModel::saveToStream(QDataStream &stream) const
{
    stream << mEnemyModelList.size();

    for(TEnemyModel *enemyModel : mEnemyModelList) {
        enemyModel->saveToStream(stream);
    }
}

int TEnemyFactoryModel::rowCount(const QModelIndex &parent) const
{
    if(!parent.isValid()) {
        return mObjectList.size();
     }
     return 0;
}

int TEnemyFactoryModel::columnCount(const QModelIndex &) const
{
    return 1;
}

QVariant TEnemyFactoryModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row<0 || row>=mObjectList.size())
        return QVariant();

    if(role == Qt::DisplayRole) {
        return tr("Factory %1").arg(row+1);
    }
    return QVariant();
}

TEnemyFactoryList TEnemyFactoryModel::enemyFactoryList() const
{
    return mObjectList;
}

TEnemyFactory *TEnemyFactoryModel::getEnemyFactory(int index)
{
    return mObjectList.at(index);
}

void TEnemyFactoryModel::setEnemyFactoryList(const TEnemyFactoryList &enemyFactoryList)
{
    mObjectList = enemyFactoryList;
}

TEnemyFactory *TEnemyFactoryModel::createEnemyFactory()
{
    return new TEnemyFactory(this);
}

TEnemyModelList TEnemyFactoryModel::enemyModelList() const
{
    return mEnemyModelList;
}

TEnemyModel *TEnemyFactoryModel::getEnemyModel(int index)
{
    return mEnemyModelList.at(index);
}

void TEnemyFactoryModel::setEnemyModelList(const TEnemyModelList &enemyModelList)
{
    mEnemyModelList = enemyModelList;
}

void TEnemyFactoryModel::onObjectInserted(const TObjectList &, const QList<int> &indexList)
{
    emit objectInserted(mObjectList, indexList);
}

void TEnemyFactoryModel::onObjectRemoved(const TObjectList &, const QList<int> &indexList)
{
    emit objectRemoved(mObjectList, indexList);
}
