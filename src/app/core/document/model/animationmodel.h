#ifndef TANIMATIONSMODEL_H
#define TANIMATIONSMODEL_H

#include "framemodel.h"
#include "entity/animation.h"
#include "objectgeneric.hpp"
#include "genericmodel.h"

class TAnimationModel : public TGenericModel<TAnimation>
{
    Q_OBJECT

public:
    explicit TAnimationModel(QObject *parent = nullptr);
    ~TAnimationModel();

    void clear();
    TFrameModelList frameModelList() const;
    void setFrameModelList(const TFrameModelList &frameModelList);
    TFrameModel *getFrameModel(int index) const;

signals:
    void objectInserted(const TAnimationList &objectList, const QList<int> &indexList);
    void objectRemoved(const TAnimationList &objectList, const QList<int> &indexList);

private:
    TFrameModelList mFrameModelList;
    QMap<TAnimation*, TFrameModel*> mAnimationMap;

    // TIO interface
public:
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;

    QList<int> removeFromContainer(TFrameModelList &container, TFrameModelList &objectList);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

    // TGenericModel interface
protected:
    virtual void onObjectInserted(const TObjectList &objectList, const QList<int> &indexList) Q_DECL_OVERRIDE;
    virtual void onObjectRemoved(const TObjectList &objectList, const QList<int> &indexList) Q_DECL_OVERRIDE;
};

#endif // TANIMATIONSMODEL_H
