#ifndef TOBJECTCONTAINER_H
#define TOBJECTCONTAINER_H

#include <QWidget>
#include <QSpinBox>
#include <QAction>

#include "objectlistview.h"

class TObjectcontainer : public QWidget
{
    Q_OBJECT

public:
    explicit TObjectcontainer(QWidget *parent = 0);
    ~TObjectcontainer();

    TObjectListView *getobjectListView() const;

private:
    TObjectListView *mObjectListView;
};

#endif // TOBJECTCONTAINER_H
