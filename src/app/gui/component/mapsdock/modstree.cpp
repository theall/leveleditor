#include "modstree.h"
#include <QHeaderView>
#include <QMouseEvent>
#include <QAbstractItemModel>

TModsTree::TModsTree(QWidget *parent) :
    QTreeView(parent)
{
    setRootIsDecorated(true);
    setHeaderHidden(true);
    setItemsExpandable(true);
    //setUniformRowHeights(true);

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

void TModsTree::mouseDoubleClickEvent(QMouseEvent *event)
{
    QAbstractItemModel *m = model();
    if(!m)
        return;

    QModelIndex clickedIndex = indexAt(event->pos());
    emit modelIndexDoubleClicked(clickedIndex);
}

void TModsTree::setModel(QAbstractItemModel *model)
{
    QTreeView::setModel(model);

    expandAll();
}
