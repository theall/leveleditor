#ifndef TSHORTCUTMODEL_H
#define TSHORTCUTMODEL_H

#include <QStandardItemModel>

#include "module/shortkeymanager.h"

class TShortcutModel: public QStandardItemModel
{
public:
    TShortcutModel(QObject *parent = 0);

    void setFilter(QString filter=QString());
    void updateShortcut();

private:
    QString mFilter;
    QStringList mDuplicatedShortcuts;
    void load(QString filter=QString());
    void setShortcutList(QStringList shortcuts);

    // QAbstractItemModel interface
public:
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

};

#endif // TSHORTCUTMODEL_H
