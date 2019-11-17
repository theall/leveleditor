#include "centralwidget.h"

#include <QSplitter>
#include <QVBoxLayout>

TCentralWidget::TCentralWidget(QWidget *parent) :
    QWidget(parent)
  , mTabWidget(new TTabWidget(this))
{
    QVBoxLayout *vbl = new QVBoxLayout;//垂直排列
    vbl->setMargin(0);//设置页边距
    vbl->addWidget(mTabWidget);
    setLayout(vbl);//设置当前布局为垂直排列

#ifdef GUI_STAND_ALONE
    for(int i=0;i<10;i++)
    {
        mTabWidget->addTab((void*)(i+0xffff), QString("Map %1").arg(i+1));
    }
#endif
}

TCentralWidget::~TCentralWidget()
{

}

TTabWidget *TCentralWidget::tabWidget() const
{
    return mTabWidget;
}
