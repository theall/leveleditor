#include "layerview.h"
#include "iconcheckdelegate.h"
#include "boldcurrentitemdelegate.h"

#include <QHeaderView>

#define COLUMN_INDEX_NAME 0
#define COLUMN_INDEX_VISIBILITY 1
#define COLUMN_INDEX_LOCK 2

TLayerView::TLayerView(QWidget *parent):
    QTreeView(parent)
  , mActionMoveLayerUp(new QAction(this))
  , mActionMoveLayerDown(new QAction(this))
  , mActionToggleOtherLayers(new QAction(this))
  , mContextMenu(new QMenu(this))
{
    setRootIsDecorated(false);
    setHeaderHidden(true);
    setItemsExpandable(false);
    setUniformRowHeights(true);
}

QSize TLayerView::sizeHint() const
{
    return QSize(130, 100);
}

QMenu *TLayerView::contextMenu()
{
    return mContextMenu;
}

void TLayerView::slotCurrentRowChanged(const QModelIndex &index)
{

}

void TLayerView::slotPressed(const QModelIndex &index)
{

}

void TLayerView::slotOnActivated(const QModelIndex &index)
{

}

void TLayerView::contextMenuEvent(QContextMenuEvent *event)
{

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

void TLayerView::slotSelectionChanged(const QItemSelection &selected,
                                   const QItemSelection &deselected)
{
    QTreeView::selectionChanged(selected, deselected);
    QModelIndexList selectedRows = selectionModel()->selectedRows();
    QList<int> rows;
    foreach (const QModelIndex &index, selectedRows) {
        rows.append(index.row());
    }

    emit onSelectionChanged(rows);
}

void TLayerView::setModel(QAbstractItemModel *model)
{
    QTreeView::setModel(model);

    QHeaderView *h = header();
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::ExtendedSelection);

    setItemDelegateForColumn(COLUMN_INDEX_NAME, new TBoldCurrentItemDelegate(selectionModel(), this));
    setItemDelegateForColumn(COLUMN_INDEX_VISIBILITY, new TIconCheckDelegate(TIconCheckDelegate::Visibility, true, this));
    setItemDelegateForColumn(COLUMN_INDEX_LOCK, new TIconCheckDelegate(TIconCheckDelegate::Lock, true, this));
    h->setStretchLastSection(false);

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
    foreach (int row, rows) {
        QModelIndex index = m->index(row, 0);
        selectionModel()->select(index, QItemSelectionModel::Select |  QItemSelectionModel::Rows);
    }

    if(newRow>=0)
        scrollTo(m->index(newRow, 0));
}
