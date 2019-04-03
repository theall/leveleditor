#include "centralwidget.h"

#include <QSplitter>
#include <QVBoxLayout>

TCentralWidget::TCentralWidget(QWidget *parent) :
    QWidget(parent)
  , mTabWidget(new TTabWidget(this))
{
    QVBoxLayout *vbl = new QVBoxLayout;
    vbl->setMargin(0);
    vbl->addWidget(mTabWidget);
    setLayout(vbl);

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
