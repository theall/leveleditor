#include "boxesmodel.h"

TBoxesModel::TBoxesModel(QObject *parent) :
    TBaseModel(parent)
{
    setName(tr("Box"));
}

void TBoxesModel::clear()
{

}

void TBoxesModel::readFromStream(QDataStream &stream)
{
    int boxAmount = 0;
    stream >> boxAmount;
    mBoxList.clear();
    for(int i=0;i<boxAmount;i++) {
        TBox *box = new TBox(this);
        box->readFromStream(stream);
        mBoxList.append(box);
    }
}

void TBoxesModel::saveToStream(QDataStream &stream) const
{

}

int TBoxesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mBoxList.size();
}

int TBoxesModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant TBoxesModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row>=0 && row<mBoxList.size())
    {
        if(role==Qt::DisplayRole)
        {
            return tr("Box %d").arg(row+1);
        }
    }
    return QVariant();
}

TBoxList TBoxesModel::boxList() const
{
    return mBoxList;
}
