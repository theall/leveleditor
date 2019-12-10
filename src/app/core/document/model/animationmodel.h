#ifndef TANIMATIONSMODEL_H
#define TANIMATIONSMODEL_H

#include "framemodel.h"
#include "entity/animation.h"
#include "objectgeneric.hpp"

class TBaseModel;
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
    TAnimationList mAnimationList;
    TFrameModelList mFrameModelList;
    QMap<TAnimation*, TFrameModel*> mAnimationMap;

    // TIO interface
public:
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

public:
    DECL_GENERIC_FUNCTIONS(Animation);

signals:
    DECL_GENERIC_SIGNALS(Animation);

    // TBaseModel interface
protected:
    virtual void onObjectInserted(const TObjectList &objectList, const QList<int> &indexList) Q_DECL_OVERRIDE;
    virtual void onObjectRemoved(const TObjectList &objectList, const QList<int> &indexList) Q_DECL_OVERRIDE;
};

#endif // TANIMATIONSMODEL_H
