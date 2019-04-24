#ifndef TCHARACTERMODEL_H
#define TCHARACTERMODEL_H

#include <QAbstractListModel>
#include "../assets/faceid.h"

class TCharacterModel : public QAbstractListModel
{
public:
    explicit TCharacterModel(QObject *parent = Q_NULLPTR);
    ~TCharacterModel();

    TFaceList faceList() const;
    void setFaceList(const TFaceList &faceList);

private:
    TFaceList mFaceList;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
};

#endif // TCHARACTERMODEL_H
