#include "objectlistview.h"

#include <QTableView>
#include <QHeaderView>
#include <QResizeEvent>

TObjectListView::TObjectListView(QWidget *parent):
    QTableView(parent)
{
    setObjectName(QStringLiteral("AnimationListView"));
    setFrameShape(QFrame::Panel);
    setFrameShadow(QFrame::Sunken);
    setSelectionBehavior(QAbstractItemView::SelectItems);
    setSelectionMode(QAbstractItemView::ExtendedSelection);

    horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    horizontalHeader()->setVisible(false);
    verticalHeader()->setVisible(false);
    verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    setLayoutDirection(Qt::LeftToRight);

    setShowGrid(false);
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

void TObjectListView::selectIndex(int index)
{
    QTableView::selectColumn(index);

    emit indexSelected(index);
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

void TObjectListView::dragMoveEvent(QDragMoveEvent *event)
{
    if(event->source()==this) {
        QModelIndex i = indexAt(event->pos());
        QRect rt;
        if(i.isValid()) {
            rt = visualRect(i);
            rt.setLeft(rt.left()-1);
        } else {
            QAbstractItemModel *m = model();
            i = m->index(m->rowCount()-1, m->columnCount()-1);
            rt = visualRect(i);
            rt.setLeft(rt.right()+1);
        }
        rt.setTop(0);
        rt.setWidth(1);
        if(rt != mHighlightRect)
        {
            mHighlightRect = rt;
            viewport()->update();
        }
        event->accept();
    } else {
        event->ignore();
    }
}

void TObjectListView::mousePressEvent(QMouseEvent *event)
{
    QModelIndex index = indexAt(event->pos());
    emit indexPressed(getIndex(index));
    QTableView::mousePressEvent(event);

}


