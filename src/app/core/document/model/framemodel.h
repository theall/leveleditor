#ifndef FRAMEMODEL_H
#define FRAMEMODEL_H

#include "basemodel.h"
#include "entity/animation.h"

class TFrameModel : public TBaseModel
{
    Q_OBJECT

public:
    explicit TFrameModel(QObject *parent = nullptr);
    ~TFrameModel();

    void clear();
    TAnimation *animation() const;
    void setAnimation(TAnimation *animation);
    QIcon getIcon() const;
    TPropertySheet *getPropertySheet() const;
    TPropertySheet *getFramePropertySheet(int index) const;
    TFrame *getFrame(int index) const;

private:
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
};

typedef QList<TFrameModel*> TFrameModelList;
#endif // FRAMEMODEL_H
