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
}

TCentralWidget::~TCentralWidget()
{

}

TTabWidget *TCentralWidget::tabWidget() const
{
    return mTabWidget;
}
