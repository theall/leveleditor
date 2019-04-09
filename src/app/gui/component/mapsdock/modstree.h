#ifndef TMODSTREE_H
#define TMODSTREE_H

#include <QEvent>
#include <QTreeView>
#include "mapsviewmodel.h"

class TModsTree : public QTreeView
{
    Q_OBJECT

public:
    explicit TModsTree(QWidget *parent = Q_NULLPTR);
    ~TModsTree();

    TMapsViewModel *mapsViewModel() const;
    void setMapsViewModel(TMapsViewModel *mapsViewModel);

private slots:
    void slotOnModuleAdded(TModule *module);
    void slotOnModuleRemoved(TModule *module, int index);

private:
    TMapsViewModel *mMapsViewModel;
    void retranslateUi();

    // QWidget interface
protected:
    void changeEvent(QEvent *) Q_DECL_OVERRIDE;
};

#endif // TMODSTREE_H
