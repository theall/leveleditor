#include "objectlistview.h"

#include <QTreeView>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QMouseEvent>
#include <QItemSelectionModel>

TObjectListView::TObjectListView(QWidget *parent):
    QTableView(parent)
{
    setObjectName(QStringLiteral("ObjectListView"));
    setFrameShape(QFrame::Panel);
    setFrameShadow(QFrame::Sunken);
    setSelectionBehavior(QAbstractItemView::SelectItems);
    setSelectionMode(QAbstractItemView::ExtendedSelection);

    horizontalHeader()->setStretchLastSection(true);
    horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    horizontalHeader()->setVisible(false);
    verticalHeader()->setVisible(false);

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

void TObjectListView::selectRow(int row, QModelIndex &)
{
    QAbstractItemModel *m = model();
    if(m)
    {
        QTableView::selectRow(row);
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
    QTableView::setModel(model);
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
    QTableView::mousePressEvent(event);
    QModelIndex modelIndex = indexAt(event->pos());
    int row = modelIndex.row();
    if(row != -1)
        emit indexPressed(modelIndex);
}

void TObjectListView::mouseMoveEvent(QMouseEvent *event)
{
    QTableView::mouseMoveEvent(event);

}

