#include "objectlistview.h"

#include <QTreeView>
#include <QHeaderView>
#include <QResizeEvent>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QItemSelectionModel>

TObjectListView::TObjectListView(QWidget *parent):
    QTreeView(parent)
{
    setObjectName(QStringLiteral("ObjectListView"));
    setFrameShape(QFrame::Panel);
    setFrameShadow(QFrame::Sunken);
    setSelectionBehavior(QAbstractItemView::SelectItems);
    setSelectionMode(QAbstractItemView::ExtendedSelection);

    header()->hide();
    setLayoutDirection(Qt::LeftToRight);
}

TObjectListView::~TObjectListView()
{

}

QList<int> TObjectListView::getSelectedIndexes()
{
    QList<int> selectedRows;
    for(QModelIndex index : selectionModel()->selectedIndexes())
    {
        int i = getIndex(index);
        if(i != -1)
            selectedRows.append(i);
    }
    qSort(selectedRows);
    return selectedRows;
}

int TObjectListView::getCurrentIndex()
{
    return getIndex(currentIndex());
}

void TObjectListView::selectRow(int row, QModelIndex &parent)
{
    QAbstractItemModel *m = model();
    if(m)
    {
        QItemSelectionModel *itemSelectionModel = selectionModel();
        QModelIndex headModelIndex = m->index(row, 0, parent);
        QItemSelection itemSelection(headModelIndex, headModelIndex);
        itemSelectionModel->select(itemSelection, QItemSelectionModel::ClearAndSelect);
        verticalScrollBar()->setSliderPosition(row);
        emit indexSelected(row);
    }
}

void TObjectListView::selectItems(QList<int> posList, bool locate)
{
    QItemSelectionModel *selModel = selectionModel();
    if(!selModel)
        return;

    selModel->clearSelection();
    QAbstractItemModel *m = model();
    int indexSize = posList.size();
    if(!m || !selModel || indexSize<=0)
        return;

    int colCount = m->columnCount();
    int row = -1;
    int col = -1;
    for(int i : posList) {
        row = i/colCount;
        col = i%colCount;
        selModel->select(m->index(row, col), QItemSelectionModel::Select);
    }

    if(locate)
    {
        scrollTo(m->index(row, col), QAbstractItemView::PositionAtCenter);
    }
}

QString TObjectListView::getCheckMimeType() const
{
    return mCheckMimeType;
}

void TObjectListView::setCheckMimeType(const QString &checkMimeType)
{
    mCheckMimeType = checkMimeType;
}

void TObjectListView::setModel(QAbstractItemModel *model)
{
    QTreeView::setModel(model);
    expandAll();
}

int TObjectListView::getIndex(const QModelIndex &index)
{
    QAbstractItemModel *m = model();
    if(!m)
        return -1;

    int columnSize = m->columnCount();
    return columnSize*index.row()+index.column();
}

void TObjectListView::mousePressEvent(QMouseEvent *event)
{
    QTreeView::mousePressEvent(event);
    QModelIndex row = indexAt(event->pos());
    emit indexPressed(row);
}

