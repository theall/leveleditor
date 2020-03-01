#include "layerview.h"
#include "iconcheckdelegate.h"
#include "boldcurrentitemdelegate.h"

#include <QHeaderView>

#define COLUMN_INDEX_NAME 0
#define COLUMN_INDEX_VISIBILITY 1
#define COLUMN_INDEX_LOCK 2

TLayerView::TLayerView(QWidget *parent):
    QTreeView(parent)
  , mActionShow(new QAction(this))
  , mActionHide(new QAction(this))
  , mActionLock(new QAction(this))
  , mActionUnLock(new QAction(this))
  , mContextMenu(new QMenu(this))
{
    setRootIsDecorated(false);//是否显示展开和折叠
    setHeaderHidden(true);//是否不保留标题
    setItemsExpandable(false);
    setUniformRowHeights(true);//判断每一项高度是否相同 如果相同就会进行一些优化

    mContextMenu->addAction(mActionShow);
    mContextMenu->addAction(mActionHide);
    mContextMenu->addSeparator();//分隔符
    mContextMenu->addAction(mActionLock);
    mContextMenu->addAction(mActionUnLock);

    connect(mActionShow, SIGNAL(triggered(bool)), this, SLOT(slotActionShowTriggered(bool)));//开眼
    connect(mActionHide, SIGNAL(triggered(bool)), this, SLOT(slotActionHideTriggered(bool)));//关眼
    connect(mActionLock, SIGNAL(triggered(bool)), this, SLOT(slotActionLockTriggered(bool)));//上锁
    connect(mActionUnLock, SIGNAL(triggered(bool)), this, SLOT(slotActionUnLockTriggered(bool)));//开锁
    mActionShow->setDisabled(true);
    mActionUnLock->setDisabled(true);
    retranslateUi();
}

QSize TLayerView::sizeHint() const
{
    return QSize(130, 100);
}

QMenu *TLayerView::contextMenu()
{
    return mContextMenu;
}

void TLayerView::changeEvent(QEvent *e)
{
    QTreeView::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange://翻译已更改
        retranslateUi();
        break;
    default:
        break;
    }
}

void TLayerView::slotCurrentChanged(const QModelIndex &current, const QModelIndex &)
{
    emit currentRowChanged(current.row());
}

//void TLayerView::slotbuttonCurrentChanged(const QModelIndex &current, const QModelIndex &previours)
//{
//    emit buttoncurrentRowChanged(current.row());
//}

void TLayerView::slotPressed(const QModelIndex &index)
{

}

void TLayerView::slotOnActivated(const QModelIndex &)
{

}

void TLayerView::contextMenuEvent(QContextMenuEvent *event)
{
    mContextMenu->popup(event->globalPos());
}

void TLayerView::keyPressEvent(QKeyEvent *event)
{
    const QModelIndex index = currentIndex();
    if (!index.isValid())
        return;

    if (event->key() == Qt::Key_Delete) {
        emit requestRemoveObject(index.row());
        return;
    }

    QTreeView::keyPressEvent(event);
}

void TLayerView::slotOnSectionResized(int logicalIndex)
{
    if (logicalIndex != 0)
        return;
}

void TLayerView::slotSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    QTreeView::selectionChanged(selected, deselected);
    QModelIndexList selectedRows = selectionModel()->selectedRows();
    QList<int> rows;
    foreach (const QModelIndex &index, selectedRows) {
        rows.append(index.row());
    }

    emit onSelectionChanged(rows);
}

void TLayerView::slotActionShowTriggered(bool)
{
    emit requestShowLayers(getSelectedRows(), true);
}

void TLayerView::slotActionHideTriggered(bool)
{
    emit requestShowLayers(getSelectedRows(), false);
}

void TLayerView::slotActionLockTriggered(bool)
{
    emit requestLockLayers(getSelectedRows(), true);
}

void TLayerView::slotActionUnLockTriggered(bool)
{
    emit requestLockLayers(getSelectedRows(), false);
}

void TLayerView::setActionShowHideState(bool state)
{
    mActionShow->setDisabled(!state);
    mActionHide->setDisabled(state);
}

void TLayerView::setActionLockUnLockState(bool state)
{
    mActionLock->setDisabled(!state);
    mActionUnLock->setDisabled(state);
}

void TLayerView::retranslateUi()
{
    mActionShow->setText(tr("Show"));
    mActionHide->setText(tr("Hide"));
    mActionLock->setText(tr("Lock"));
    mActionUnLock->setText(tr("Unlock"));
}

QList<int> TLayerView::getSelectedRows() const
{
    QSet<int> rows;
    QItemSelectionModel *sm = selectionModel();//定义一个QItemSelectionModel接受返回的指针 返回当前选择模型
    if(sm) {    //该指针不为空
        for(QModelIndex index : sm->selectedIndexes()) {//选定索引
            rows.insert(index.row());//如果值不在集合中 则将项值插入集合
        }
    }
    return rows.toList();//返回一个新列表 包含集合中的元素
}

void TLayerView::setModel(QAbstractItemModel *model)
{
    QTreeView::setModel(model);

    if(!model)
        return;

    Q_ASSERT(model->columnCount()>=3);

    QHeaderView *h = header();
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::ExtendedSelection);

    setItemDelegateForColumn(COLUMN_INDEX_NAME, new TBoldCurrentItemDelegate(selectionModel(), this));
    setItemDelegateForColumn(COLUMN_INDEX_VISIBILITY, new TIconCheckDelegate(TIconCheckDelegate::Visibility, true, this));
    setItemDelegateForColumn(COLUMN_INDEX_LOCK, new TIconCheckDelegate(TIconCheckDelegate::Lock, true, this));
    h->setStretchLastSection(false);

    QItemSelectionModel *sm = selectionModel();
    connect(sm, SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(slotCurrentChanged(QModelIndex,QModelIndex)));
    connect(this, SIGNAL(pressed(QModelIndex)), SLOT(slotPressed(QModelIndex)));
    connect(this, SIGNAL(activated(QModelIndex)), SLOT(slotOnActivated(QModelIndex)));
    connect(h, SIGNAL(sectionResized(int,int,int)), this, SLOT(slotOnSectionResized(int)));

    //QItemSelectionModel *button = selectionModel();
//    connect(button, SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(slotbuttonCurrentChanged(QModelIndex,QModelIndex)));

    h->setSectionResizeMode(COLUMN_INDEX_NAME, QHeaderView::Stretch);
    h->setSectionResizeMode(COLUMN_INDEX_VISIBILITY, QHeaderView::Fixed);
    h->setSectionResizeMode(COLUMN_INDEX_LOCK, QHeaderView::Fixed);

    const int iconSectionWidth = TIconCheckDelegate::exclusiveSectionWidth();
    h->setMinimumSectionSize(iconSectionWidth);
    h->resizeSection(COLUMN_INDEX_VISIBILITY, iconSectionWidth);
    h->resizeSection(COLUMN_INDEX_LOCK, iconSectionWidth);
}

void TLayerView::selectRows(QList<int> rows, int newRow)
{
    QAbstractItemModel *m = model();
    if(!m)
        return;

    clearSelection();

    QItemSelectionModel *sm = selectionModel();
    foreach (int row, rows) {
        QModelIndex index = m->index(row, 0);
        sm->select(index, QItemSelectionModel::Select |  QItemSelectionModel::Rows);
    }

    if(newRow>=0)
        scrollTo(m->index(newRow, 0));
}

void TLayerView::selectFirst()
{
    selectRow(0);
}

void TLayerView::selectLast()
{
    QAbstractItemModel *m = model();
    if(!m)
        return;

    selectRow(m->rowCount()-1);
}

void TLayerView::selectRow(int row)
{
    QAbstractItemModel *m = model();
    if(!m)
        return;

    QItemSelectionModel *sm = selectionModel();
    QModelIndex index = m->index(row, 0);
    sm->select(index, QItemSelectionModel::Select |  QItemSelectionModel::Rows);
}
