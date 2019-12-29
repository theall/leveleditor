#include "objectcontainer.h"

#include <QToolBar>
#include <QSplitter>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

TObjectContainer::TObjectContainer(QWidget *parent) :
    QWidget(parent)
{
    QToolBar *toolbar = new QToolBar(this);


    setObjectName(QStringLiteral("Objectcontainer"));
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    QVBoxLayout *verticalLayout = new QVBoxLayout(this);
    verticalLayout->addWidget(toolbar);

    verticalLayout->setSpacing(1);
    verticalLayout->setMargin(3);

    mObjectListView = new TObjectListView(this);
    mSubControlObjectListView = new TSubControlObjectListView(this);
    verticalLayout->addWidget(mObjectListView);
    verticalLayout->addWidget(mSubControlObjectListView);
    setLayout(verticalLayout);
}

TObjectContainer::~TObjectContainer()
{

}

TObjectListView *TObjectContainer::getobjectListView() const
{
    return mObjectListView;
}

TSubControlObjectListView *TObjectContainer::getSubControlObjectListView() const
{
    return mSubControlObjectListView;
}


