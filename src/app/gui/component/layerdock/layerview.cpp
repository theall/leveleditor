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
    setRootIsDecorated(false);
    setHeaderHidden(true);
    setItemsExpandable(false);
    setUniformRowHeights(true);

    mContextMenu->addAction(mActionShow);
    mContextMenu->addAction(mActionHide);
    mContextMenu->addSeparator();
    mContextMenu->addAction(mActionLock);
    mContextMenu->addAction(mActionUnLock);

    connect(mActionShow, SIGNAL(triggered(bool)), this, SLOT(slotActionShowTriggered(bool)));
    connect(mActionHide, SIGNAL(triggered(bool)), this, SLOT(slotActionHideTriggered(bool)));
    connect(mActionLock, SIGNAL(triggered(bool)), this, SLOT(slotActionLockTriggered(bool)));
    connect(mActionUnLock, SIGNAL(triggered(bool)), this, SLOT(slotActionUnLockTriggered(bool)));

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
    case QEvent::LanguageChange:
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

void TLayerView::slotPressed(const QModelIndex &index)
{

}

void TLayerView::slotOnActivated(const QModelIndex &index)
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
    QItemSelectionModel *sm = selectionModel();
    if(sm) {
        for(QModelIndex index : sm->selectedIndexes()) {
            rows.insert(index.row());
        }
    }
    return rows.toList();
}

void TLayerView::setModel(QAbstractItemModel *model)
{
    QTreeView::setModel(model);

    if(!model)
        return;

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
