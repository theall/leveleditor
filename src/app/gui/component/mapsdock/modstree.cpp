#include "modstree.h"
#include <QHeaderView>

TModsTree::TModsTree(QWidget *parent) :
    QTreeView(parent)
{
    setRootIsDecorated(true);
    setHeaderHidden(true);
    setItemsExpandable(true);
    setUniformRowHeights(true);

    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
}

TModsTree::~TModsTree()
{

}

void TModsTree::retranslateUi()
{

}

void TModsTree::changeEvent(QEvent *event)
{
    if (event->type()==QEvent::LanguageChange)
    {
        retranslateUi();//update ui
    }

    QTreeView::changeEvent(event);
}
