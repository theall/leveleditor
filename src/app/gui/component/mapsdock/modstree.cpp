#include "modstree.h"
#include <QHeaderView>
#include <QMouseEvent>
#include <QAbstractItemModel>

TModsTree::TModsTree(QWidget *parent) :
    QTreeView(parent)
  , mMenu(nullptr)
{
    setRootIsDecorated(true);//此属性保留是否显示用于展开和折叠顶级项的控件。默认情况为true
    setHeaderHidden(true);//标题隐藏 默认为false
    setItemsExpandable(true);//此属性保留项目是否可由用户展开。此属性保留用户是否可以交互展开和折叠项。默认情况下，此属性为true。
    //setUniformRowHeights(true);不注释显示 启动程序失败，路径或者权限错误?

    setSelectionBehavior(QAbstractItemView::SelectRows);
    //此属性保留视图使用的选择行为。此属性保留是按单个项、行还是列进行选择。（仅选择行。）
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    //当用户以通常的方式选择一个项目时，将清除选择并选择新项目。
    //但是，如果用户在单击某个项目时按Ctrl键，则会切换单击的项目，而所有其他项目都不会被触碰。
    //如果用户在单击项目时按Shift键，则当前项目和单击的项目之间的所有项目都将被选中或取消选中，
    //具体取决于单击的项目的状态。可以通过在多个项目上拖动鼠标来选择它们。
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),this,SLOT(slotCustomContextMenuRequested(const QPoint &)));
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

void TModsTree::mousePressEvent(QMouseEvent *event)
{
    QTreeView::mousePressEvent(event);
    mIndex = indexAt(event->pos());
}

void TModsTree::setModel(QAbstractItemModel *model)
{
    QTreeView::setModel(model);

    expandAll();
}

void TModsTree::slotCustomContextMenuRequested(const QPoint &pos)
{
    if(!mMenu) {
        mMenu = new QMenu(this);
        connect(mMenu,SIGNAL(triggered(QAction*)),this,SLOT(slotActionTriggered(QAction*)));
    }
    mMenu->show();
    mMenu->clear();
    QAction *open = new QAction(tr("打开"), mMenu);
    mMenu->addAction(open);
    mMenu->popup(QCursor::pos());
}

void TModsTree::slotActionTriggered(QAction *open)
{
        emit modelIndexDoubleClicked(mIndex);
}
