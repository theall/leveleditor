#include "tabcontainer.h"

#include <QVBoxLayout>
#include <QSplitter>

TTabContainer::TTabContainer(QWidget *parent) :
    QWidget(parent)
  , mGraphicsView(new TGraphicsView)
{
    mGraphicsView->setFrameShape(QFrame::Panel);
    mGraphicsView->setFrameShadow(QFrame::Sunken);

    QVBoxLayout *vboxLayout = new QVBoxLayout;
    vboxLayout->addWidget(mGraphicsView);
    setLayout(vboxLayout);
}

TTabContainer::~TTabContainer()
{

}

TGraphicsView *TTabContainer::graphicsView() const
{
    return mGraphicsView;
}

QGraphicsScene *TTabContainer::graphicsScene()
{
    return mGraphicsView->scene();
}

void TTabContainer::setGraphicsScene(QGraphicsScene *scene)
{
    mGraphicsView->setScene(scene);
}
