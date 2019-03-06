#include "eventsmodel.h"

TEventsModel::TEventsModel(QObject *parent) :
    QAbstractTableModel(parent)
{

}

void TEventsModel::clear()
{
    mEventList.clear();
}

void TEventsModel::readFromStream(QDataStream &stream)
{
    mEventList.clear();

    int event;
    for(int i=0;i<100;i++) {
        stream >> event;
        mEventList.append(event);
    }
}

void TEventsModel::saveToStream(QDataStream &stream) const
{
    for(int i=0;i<100;i++) {
        stream << mEventList.at(i);
    }
}

int TEventsModel::rowCount(const QModelIndex &parent) const
{
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
