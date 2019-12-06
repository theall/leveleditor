#ifndef TOBJECTDOCK_H
#define TOBJECTDOCK_H

#include <QAction>
#include <QToolBar>

#include "objectcontainer.h"
#include "objectlistview.h"
#include "../basedock.h"
class TObjectDock:public TBaseDock
{
    Q_OBJECT
public:
    TObjectDock(QWidget *parent = nullptr);
    ~TObjectDock();

public:
    void retranslateUi() Q_DECL_OVERRIDE;
    TObjectListView *getTObjectcontainer() const;

private:
    TObjectcontainer *mObjectcontainer;
};

#endif // TOBJECTDOCK_H
