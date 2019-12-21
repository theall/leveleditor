#include "eventmodel.h"

#define EVENT_COUNT 100

TEventModel::TEventModel(QObject *parent) :
    TBaseModel(TBaseModel::EVENT, parent)
{
    setName(tr("Event"));

    for(int i=0;i<EVENT_COUNT;i++) {
        mEventList.append(0);
    }
}

void TEventModel::clear()
{
    mEventList.clear();
}

void TEventModel::readFromStream(QDataStream &stream)
{
    mEventList.clear();

    int event;
    for(int i=0;i<EVENT_COUNT;i++) {
        stream >> event;
        mEventList.append(event);
    }
}

void TEventModel::saveToStream(QDataStream &stream) const
{
    for(int i=0;i<EVENT_COUNT;i++) {
        stream << mEventList.at(i);
    }
}

int TEventModel::rowCount(const QModelIndex &parent) const
{
    if(!parent.isValid()) {
        return mEventList.size();
     }
     return 0;
}

int TEventModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 1;
}

QVariant TEventModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row>=0 && row<mEventList.size())
    {
        if(role==Qt::DisplayRole)
        {
            return tr("Event %1").arg(row+1);
        }
    }
    return QVariant();
}

QList<int> TEventModel::eventList() const
{
    return mEventList;
}
