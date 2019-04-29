#ifndef TANIMATIONSMODEL_H
#define TANIMATIONSMODEL_H

#include "entity/animation.h"
#include "../base/io.h"

#include <QAbstractTableModel>

class TAnimationsModel : public QAbstractTableModel, TIO
{
    Q_OBJECT

public:
    explicit TAnimationsModel(QObject *parent = nullptr);
    ~TAnimationsModel();

    TAnimationList animationList() const;
    void setAnimationList(const TAnimationList &animationList);

    void clear();

private:
    TAnimationList mAnimationList;

    // TIO interface
public:
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
};

#endif // TANIMATIONSMODEL_H
