#ifndef FRAMEMODEL_H
#define FRAMEMODEL_H

#include "basemodel.h"
#include "entity/frame.h"
#include "objectgeneric.hpp"

class TAnimation;
class TFrameModel : public TBaseModel
{
    Q_OBJECT

public:
    explicit TFrameModel(QObject *parent = nullptr);
    TFrameModel(TAnimation *animation, QObject *parent = nullptr);
    ~TFrameModel();

    void clear();
    void insetTile(TTile *tile, int index = -1);
    TAnimation *animation() const;
    void setAnimation(TAnimation *animation);
    QIcon getIcon() const;
    TPropertySheet *getPropertySheet() const;
    TPropertySheet *getFramePropertySheet(int index) const;
    TFrame *getFrame(int index) const;

private:
    TFrameList mFrameList;
    TAnimation *mAnimation;

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
    DECL_GENERIC_FUNCTIONS(Frame);

signals:
    DECL_GENERIC_SIGNALS(Frame);

    // TBaseModel interface
protected:
    virtual void onObjectInserted(const TObjectList &objectList, const QList<int> &indexList) Q_DECL_OVERRIDE;
    virtual void onObjectRemoved(const TObjectList &objectList, const QList<int> &indexList) Q_DECL_OVERRIDE;
};

typedef QList<TFrameModel*> TFrameModelList;
#endif // FRAMEMODEL_H
