#ifndef TOBJECTDOCK_H
#define TOBJECTDOCK_H

#include <QAction>
#include <QToolBar>

#include "objectcontainer.h"
#include "../basedock.h"
class TObjectDock:public TBaseDock
{
    Q_OBJECT
public:
    TObjectDock(QWidget *parent = nullptr);
    ~TObjectDock();

    TObjectListView *getObjectListView() const;
    TSubControlObjectListView *getSubControlObjectListView() const;

private:
    TObjectContainer *mObjectcontainer;


public:
    void retranslateUi() Q_DECL_OVERRIDE;
};

#endif // TOBJECTDOCK_H
