#ifndef TBASEMODEL_H
#define TBASEMODEL_H

#include <QList>
#include <QIcon>
#include <QAbstractTableModel>

#include "../base/io.h"

class TBaseModel : public QAbstractTableModel, TIO
{
public:
    explicit TBaseModel(QObject *parent = Q_NULLPTR);

    QString name() const;
    void setName(const QString &name);

    bool visible() const;
    void setVisible(bool visible);

    QIcon icon() const;
    void setIcon(const QIcon &icon);

    bool locked() const;
    void setLocked(bool locked);

private:
    QIcon mIcon;
    QString mName;
    bool mVisible;
    bool mLocked;

    // QAbstractItemModel interface
public:
    int columnCount(const QModelIndex &parent) const;
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
};
typedef QList<TBaseModel*> TBaseModelList;

#endif // TBASEMODEL_H
