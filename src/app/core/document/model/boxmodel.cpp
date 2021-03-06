#include "boxmodel.h"

TBoxModel::TBoxModel(QObject *parent) :
    TGenericModel<TBox>(TBaseModel::BOX, parent)
{
    setName(tr("Box"));
    setIcon(QIcon(":/scenemodel/images/box.png"));
}

void TBoxModel::clear()
{

}

void TBoxModel::readFromStream(QDataStream &stream)
{
    int boxAmount = 0;
    stream >> boxAmount;
    mObjectList.clear();
    for(int i=0;i<boxAmount;i++) {
        TBox *box = new TBox(this);
        box->readFromStream(stream);
        mObjectList.append(box);
    }
}

void TBoxModel::saveToStream(QDataStream &stream) const
{
    stream << mObjectList.size();
    for(TBox *box : mObjectList) {
        box->saveToStream(stream);
    }
}

int TBoxModel::rowCount(const QModelIndex &parent) const
{
    if(!parent.isValid()) {
       return mObjectList.size();
    }
    return 0;
}

int TBoxModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant TBoxModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row>=0 && row<mObjectList.size())
    {
        if(role==Qt::DisplayRole)
        {
            return tr("Box %1").arg(row+1);
        }
    }
    return QVariant();
}

void TBoxModel::onObjectInserted(const TObjectList &objectList, const QList<int> &indexList)
{
    emit objectInserted(convert(objectList), indexList);
}

void TBoxModel::onObjectRemoved(const TObjectList &objectList, const QList<int> &indexList)
{
    emit objectRemoved(convert(objectList), indexList);
}

void TBoxModel::onObjectMove(const TObjectList &objectList, const QList<int> &posList)
{

}

TBoxList TBoxModel::boxList() const
{
    return mObjectList;
}
