#include "objectcontainer.h"

#include <QToolBar>
#include <QSplitter>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

TObjectContainer::TObjectContainer(QWidget *parent) :
    QWidget(parent)
{
    setObjectName(QStringLiteral("Objectcontainer"));//保存名字
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);//小部件的缩放

    QVBoxLayout *verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSpacing(1);//将控件与控件之间的间距设为1
    verticalLayout->setMargin(3);//设置属性边缘

    mObjectListView = new TObjectListView(this);
    mSubcontrolObjectListView = new TSubcontrolObjectListView(this);
    verticalLayout->addWidget(mObjectListView);
    verticalLayout->addWidget(mSubcontrolObjectListView);
    setLayout(verticalLayout);
}

TObjectContainer::~TObjectContainer()
{

}

TObjectListView *TObjectContainer::getobjectListView() const
{
    return mObjectListView;
}

TSubcontrolObjectListView *TObjectContainer::getSubcontrolObjectListView() const
{
    return mSubcontrolObjectListView;
}




