#include "mapsproxyview.h"
#include <QVBoxLayout>

TMapsProxyView::TMapsProxyView(QWidget *parent) :
    QWidget(parent)
  , mViewMode(Tab)
  , mModsTab(new TModsTab(this))
  , mModsTree(new TModsTree(this))
{
    QVBoxLayout *vboxLayout = new QVBoxLayout;
    vboxLayout->addWidget(mModsTab);
    vboxLayout->addWidget(mModsTree);
    vboxLayout->setContentsMargins(0, 0, 0, 0);
    vboxLayout->setMargin(0);
    vboxLayout->setSpacing(0);
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
        mModsTab->setVisible(false);
        mModsTree->setVisible(true);
    } else if(mViewMode == Tab) {
        mModsTab->setVisible(true);
        mModsTree->setVisible(false);
    }
}

void TMapsProxyView::setModel(QAbstractItemModel *model)
{
    mModsTab->setModel(model);
    mModsTree->setModel(model);
}
