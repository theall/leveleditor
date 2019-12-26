#ifndef TOBJECTCONTAINER_H
#define TOBJECTCONTAINER_H

#include <QWidget>
#include <QSpinBox>
#include <QAction>

#include "objectlistview.h"
#include "subcontrolobjectlistview.h"

class TObjectContainer : public QWidget
{
    Q_OBJECT

public:
    explicit TObjectContainer(QWidget *parent = 0);
    ~TObjectContainer();

    TObjectListView *getobjectListView() const;
    TSubControlObjectListView *getSubControlObjectListView() const;

private:
    TObjectListView *mObjectListView;
    TSubControlObjectListView *mSubControlObjectListView;
};

#endif // TOBJECTCONTAINER_H
