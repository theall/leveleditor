#ifndef TTRIGGERSMODEL_H
#define TTRIGGERSMODEL_H

#include "basemodel.h"
#include "entity/trigger.h"
#include "objectgeneric.hpp"

class TTriggerModel : public TBaseModel
{
    Q_OBJECT

public:
    explicit TTriggerModel(QObject *parent = Q_NULLPTR);
    ~TTriggerModel();

    TTriggerList triggerList() const;
    void setTriggerList(const TTriggerList &triggerList);

    void clear();

private:
    TTriggerList mTriggerList;

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
    DECL_GENERIC_FUNCTIONS(Trigger);

signals:
    DECL_GENERIC_SIGNALS(Trigger);
};

#endif // TTRIGGERSMODEL_H
