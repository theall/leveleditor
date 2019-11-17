#include "mapsproxyview.h"
#include <QVBoxLayout>

TMapsProxyView::TMapsProxyView(QWidget *parent) :
    QWidget(parent)
  , mViewMode(Tab)
  , mModsTab(new TModsTab(this))
  , mModsTree(new TModsTree(this))
{
    QVBoxLayout *vboxLayout = new QVBoxLayout;//垂直排列小部件
    vboxLayout->addWidget(mModsTab);
    vboxLayout->addWidget(mModsTree);
    vboxLayout->setContentsMargins(0, 0, 0, 0);//设置上下左右的边距
    vboxLayout->setMargin(0);//外部边框的距离
    vboxLayout->setSpacing(0);//重新实现QLayout：：setspace（）。设置两个控件的上下间距
    setLayout(vboxLayout);

    connect(mModsTab,
            SIGNAL(modelIndexDoubleClicked(QModelIndex)),
            this,
            SIGNAL(modelIndexDoubleClicked(QModelIndex)));
    connect(mModsTree,
            SIGNAL(modelIndexDoubleClicked(QModelIndex)),
            this,
            SIGNAL(modelIndexDoubleClicked(QModelIndex)));

    setViewMode(Tree);
}

TMapsProxyView::~TMapsProxyView()
{

}

void TMapsProxyView::setViewMode(const TMapsProxyView::ViewMode &viewMode)
{
    mViewMode = viewMode;
    if(mViewMode == Tree) {
        mModsTab->setVisible(false);//隐藏
        mModsTree->setVisible(true);//显示
    } else if(mViewMode == Tab) {
        mModsTab->setVisible(true);//显示
        mModsTree->setVisible(false);//隐藏
    }
}

void TMapsProxyView::setModel(QAbstractItemModel *model)
{
    mModsTab->setModel(model);
    mModsTree->setModel(model);
}
