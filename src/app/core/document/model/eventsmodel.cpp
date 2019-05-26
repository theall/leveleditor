#include "eventsmodel.h"

#define EVENT_COUNT 100

TEventsModel::TEventsModel(QObject *parent) :
    TBaseModel(TBaseModel::EVENT, parent)
{
    setName(tr("Event"));

    for(int i=0;i<EVENT_COUNT;i++) {
        mEventList.append(0);
    }
}

void TEventsModel::clear()
{
    mEventList.clear();
}

void TEventsModel::readFromStream(QDataStream &stream)
{
    mEventList.clear();

    int event;
    for(int i=0;i<EVENT_COUNT;i++) {
        stream >> event;
        mEventList.append(event);
    }
}

void TEventsModel::saveToStream(QDataStream &stream) const
{
    for(int i=0;i<EVENT_COUNT;i++) {
        stream << mEventList.at(i);
    }
}

int TEventsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mEventList.size();
}

int TEventsModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 1;
}

QVariant TEventsModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row>=0 && row<mEventList.size())
    {
        if(role==Qt::DisplayRole)
        {
            return tr("Event %d").arg(row+1);
        }
    }
    return QVariant();
}

QList<int> TEventsModel::eventList() const
{
    return mEventList;
}
