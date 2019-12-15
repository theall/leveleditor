#ifndef TCHUNKMODEL_H
#define TCHUNKMODEL_H

#include <QAbstractListModel>

#include "../assets/chunkid.h"

class TChunkModel : public QAbstractListModel
{
public:
    explicit TChunkModel(QObject *parent = Q_NULLPTR);
    ~TChunkModel();

    TChunkList chunIdList() const;
    void setChunIdList(const TChunkList &chunIdList);

private:
    TChunkList mChunkList;

public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
};

#endif // TCHUNKMODEL_H
