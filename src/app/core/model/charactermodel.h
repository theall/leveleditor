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
    TFaceId *getCurrentFaceId() const;
    void setFaceList(const TFaceList &faceList);

    int getCurrentIndex() const;
    void setCurrentIndex(int currentIndex);

private:
    TFaceList mFaceList;
    int mCurrentIndex;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
};

#endif // TCHARACTERMODEL_H
