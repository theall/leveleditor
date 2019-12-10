#include "boxmodel.h"

TBoxModel::TBoxModel(QObject *parent) :
    TBaseModel(TBaseModel::BOX, parent)
{
    setName(tr("Box"));
}

void TBoxModel::clear()
{

}

void TBoxModel::readFromStream(QDataStream &stream)
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

void TBoxModel::saveToStream(QDataStream &stream) const
{
    stream << mBoxList.size();
    for(TBox *box : mBoxList) {
        box->saveToStream(stream);
    }
}

int TBoxModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mBoxList.size();
}

int TBoxModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant TBoxModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row>=0 && row<mBoxList.size())
    {
        if(role==Qt::DisplayRole)
        {
            return tr("Box %1").arg(row+1);
        }
    }
    return QVariant();
}

TBoxList TBoxModel::boxList() const
{
    return mBoxList;
}

IMPL_GENERIC_FUNCTIONS(Box)
