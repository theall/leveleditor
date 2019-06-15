#ifndef TANIMATIONSMODEL_H
#define TANIMATIONSMODEL_H

#include "basemodel.h"
#include "framemodel.h"

class TAnimationModel : public TBaseModel
{
    Q_OBJECT

public:
    explicit TAnimationModel(QObject *parent = nullptr);
    ~TAnimationModel();

    void clear();
    TFrameModelList frameModelList() const;
    void setFrameModelList(const TFrameModelList &frameModelList);
    TFrameModel *getFrameModel(int index) const;

private:
    TFrameModelList mFrameModelList;

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
