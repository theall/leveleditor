#include "objectcontainer.h"

#include <QToolBar>
#include <QSplitter>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

//#define CREATE_ACTION(action,image,func) \
//    action = toolbar->addAction(QString());\
//    action->setIcon(QIcon(image));\
//    connect(action, SIGNAL(triggered()), this, SLOT(func()))

TObjectcontainer::TObjectcontainer(QWidget *parent) :
    QWidget(parent)
{
    setObjectName(QStringLiteral("Objectcontainer"));//保存名字
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);//小部件的缩放

    QHBoxLayout *verticalLayout = new QHBoxLayout(this);
    verticalLayout->setSpacing(1);//将控件与控件之间的间距设为1
    verticalLayout->setMargin(3);//设置属性边缘

    mObjectListView = new TObjectListView(this);
    QSplitter *verticalSplitter = new QSplitter(this);//分离器
    verticalSplitter->setOrientation(Qt::Horizontal);//保留拆分器的方向为垂直
    verticalSplitter->setOpaqueResize(true);//保留大小调整是否不透明
    verticalSplitter->setHandleWidth(2);//设置拆分器句柄的宽度
    verticalSplitter->setChildrenCollapsible(true);//保留用户是否可以将子小部件的大小调整为0
    verticalSplitter->addWidget(mObjectListView);//空白区
    //verticalSplitter->setStretchFactor(0, 5);//设置控件0占5
    //verticalSplitter->setStretchFactor(1, 5);//设置控件1占5
    verticalLayout->addWidget(verticalSplitter);
}

TObjectcontainer::~TObjectcontainer()
{

}

TObjectListView *TObjectcontainer::getobjectListView() const
{
    return mObjectListView;
}




