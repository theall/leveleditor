#ifndef TMODSTAB_H
#define TMODSTAB_H

#include <QTabWidget>
#include <QAbstractItemView>
#include "mapsviewmodel.h"

class TModsTab : public QTabWidget
{
    Q_OBJECT

public:
    explicit TModsTab(QWidget *parent = Q_NULLPTR);
    ~TModsTab();

    void setMapsViewModel(TMapsViewModel *mapsViewModel);
    void setModel(QAbstractItemModel *model);

private slots:
    void slotOnModuleAdded(TModule *module, int);
    void slotOnModuleRemoved(TModule *module, int index);

private:
    TMapsViewModel *mMapsViewModel;
    void internalSetModel(QAbstractItemModel *model, const QModelIndex &index, QTabWidget *tabWidget);
};

#endif // TMODSTAB_H
