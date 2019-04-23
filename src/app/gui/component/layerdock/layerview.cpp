#include "layerview.h"

#include <QHeaderView>

TLayerView::TLayerView(QWidget *parent):
    QTreeView(parent),
    mActionMoveLayerUp(new QAction(this)),
    mActionMoveLayerDown(new QAction(this)),
    mActionToggleOtherLayers(new QAction(this)),
    mContextMenu(new QMenu(this))
{
    setRootIsDecorated(false);
    setHeaderHidden(true);
    setItemsExpandable(true);
    setUniformRowHeights(true);

    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::ExtendedSelection);

    connect(this, SIGNAL(pressed(QModelIndex)), SLOT(slotPressed(QModelIndex)));

    connect(this, SIGNAL(activated(QModelIndex)), SLOT(onActivated(QModelIndex)));

    connect(header(), SIGNAL(sectionResized(int,int,int)), this, SLOT(slotOnSectionResized(int)));
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
