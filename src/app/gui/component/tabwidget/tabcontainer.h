#ifndef TABCONTAINER_H
#define TABCONTAINER_H

#include <QWidget>
#include <QGraphicsView>

#include "graphicsview.h"

class TTabContainer : public QWidget
{
public:
    TTabContainer(QWidget *parent=nullptr);
    ~TTabContainer();

    TGraphicsView *graphicsView() const;
    QGraphicsScene *graphicsScene();
    void setGraphicsScene(QGraphicsScene *scene);

private:
    TGraphicsView *mGraphicsView;
    QGraphicsView *mActionsView;
};

#endif // TABCONTAINER_H
