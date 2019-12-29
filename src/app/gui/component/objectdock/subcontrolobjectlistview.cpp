#include "subcontrolobjectlistview.h"

#include <QHeaderView>
#include <QResizeEvent>

TSubControlObjectListView::TSubControlObjectListView(QWidget *)
{
    setObjectName(QStringLiteral("SubcontrolObjectListView"));
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
TSubControlObjectListView::~TSubControlObjectListView()
{

}

QList<int> TSubControlObjectListView::getSelectedIndexes()
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

int TSubControlObjectListView::getIndex(const QModelIndex &index)
{
    QAbstractItemModel *m = model();
    if(!m)
        return -1;

    int columnSize = m->columnCount();
    return columnSize*index.row()+index.column();
}

void TSubControlObjectListView::selectRow(int row)
{
    QTableView::selectRow(row);
}

int TSubControlObjectListView::getCurrentIndex()
{
   return getIndex(currentIndex());
}

void TSubControlObjectListView::setModel(QAbstractItemModel *model)
{
    QTableView::setModel(model);
}

void TSubControlObjectListView::mousePressEvent(QMouseEvent *event)
{
    QTableView::mousePressEvent(event);
    QModelIndex modelIndex = indexAt(event->pos());
    int row = modelIndex.row();
    if(row != -1)
        emit indexPressed(row);
}
