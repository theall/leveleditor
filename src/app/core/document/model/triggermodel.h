#ifndef TTRIGGERSMODEL_H
#define TTRIGGERSMODEL_H

#include "basemodel.h"
#include "entity/trigger.h"
#include "objectgeneric.hpp"
#include "genericmodel.h"

class TTriggerModel : public TGenericModel<TTrigger>
{
    Q_OBJECT

public:
    explicit TTriggerModel(QObject *parent = Q_NULLPTR);
    ~TTriggerModel();

    TTriggerList triggerList() const;
    void setTriggerList(const TTriggerList &triggerList);

    void clear();

signals:
    void objectInserted(const TTriggerList &objectList, const QList<int> &indexList);
    void objectRemoved(const TTriggerList &objectList, const QList<int> &indexList);

    // TIO interface
public:
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

protected:
    virtual void onObjectInserted(const TObjectList &objectList, const QList<int> &indexList) Q_DECL_OVERRIDE;
    virtual void onObjectRemoved(const TObjectList &objectList, const QList<int> &indexList) Q_DECL_OVERRIDE;
    virtual void onObjectMove(const TObjectList &objectList, const QList<int> &posList) Q_DECL_OVERRIDE;

};

#endif // TTRIGGERSMODEL_H
