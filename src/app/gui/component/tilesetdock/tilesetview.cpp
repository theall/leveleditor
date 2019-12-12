#include "tilesetview.h"

#include <QMouseEvent>
#include <QHeaderView>
#include <QContextMenuEvent>

TTilesetView::TTilesetView(QWidget *parent) :
    QTableView(parent)
  , mContextMenu(new QMenu(this))
{
    setObjectName(QStringLiteral("TilesetView"));
    setFrameShape(QFrame::Panel);
    setFrameShadow(QFrame::Sunken);

    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::ExtendedSelection);

    horizontalHeader()->setStretchLastSection(true);
    horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    horizontalHeader()->setVisible(false);
    verticalHeader()->setVisible(false);
    verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    setSortingEnabled(false);
    setShowGrid(false);

    mActionAddTiles = mContextMenu->addAction(QString(), this, SLOT(slotActionAddTilesTriggered()));
    mActionRemoveTiles = mContextMenu->addAction(QString(), this, SLOT(slotActionRemoveTilesTriggered()));
    mContextMenu->addSeparator();
    mActionShowGrid = mContextMenu->addAction(QString(), this, SLOT(slotActionShowGridTriggered(bool)));

    retranslateUi();
}

TTilesetView::~TTilesetView()
{

}

QList<int> TTilesetView::getSelectedIndexes()
{
    QSet<int> selectedRows;
    for(QModelIndex index : selectionModel()->selectedIndexes())
    {
        selectedRows.insert(index.row());
    }
    return selectedRows.toList();
}

int TTilesetView::currentRow()
{
    return currentIndex().row();
}

void TTilesetView::selectRow(int row)
{
    if(model())
    {
        QTableView::selectRow(row);
        emit rowSelected(row);
    }
}

int TTilesetView::rowCount()
{
    QAbstractItemModel *m = model();
    return m?m->rowCount():0;
}

void TTilesetView::slotActionShowGridTriggered(bool checked)
{
    setShowGrid(checked);
}

void TTilesetView::slotActionAddTilesTriggered()
{

}

void TTilesetView::slotActionRemoveTilesTriggered()
{

}

void TTilesetView::slotActionRenameTriggered()
{

}

void TTilesetView::slotSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(selected);
    Q_UNUSED(deselected);

    emit hasSelectionChanged(getSelectedIndexes().size()>0);
}

void TTilesetView::slotOnCurrentChanged(const QModelIndex &current, const QModelIndex &)
{
    emit currentRowChanged(current.row());
}

void TTilesetView::retranslateUi()
{
    mActionAddTiles->setText(tr("Add tiles"));
    mActionRemoveTiles->setText(tr("Remove tiles"));
    mActionShowGrid->setText("Show grid");
}

void TTilesetView::setModel(QAbstractItemModel *model)
{
    QTableView::setModel(model);
    emit validChanged(model!=nullptr);

    if(model)
    {
        QItemSelectionModel *itemSelectionModel = selectionModel();
        connect(itemSelectionModel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(slotSelectionChanged(QItemSelection,QItemSelection)));
        connect(itemSelectionModel, SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(slotOnCurrentChanged(QModelIndex,QModelIndex)));
    }
}

int TTilesetView::sizeHintForRow(int row) const
{
    QAbstractItemModel *m = model();
    if(!m)
        return 0;

    int imageMaxHeight = 0;
    int columnCount = m->columnCount();
    for(int i=0;i<columnCount;i++) {
        QPixmap p = m->data(m->index(row,i), Qt::DecorationRole).value<QPixmap>();
        int pixmapHeight = p.height();
        if(imageMaxHeight < pixmapHeight)
            imageMaxHeight = pixmapHeight;
    }
    return imageMaxHeight;
}

int TTilesetView::sizeHintForColumn(int column) const
{
    QAbstractItemModel *m = model();
    if(!m)
        return 0;

    int imageMaxWidth = 0;
    int columnCount = m->rowCount();
    for(int i=0;i<columnCount;i++) {
        QPixmap p = m->data(m->index(i,column), Qt::DecorationRole).value<QPixmap>();
        int pixmapHeight = p.height();
        if(imageMaxWidth < pixmapHeight)
            imageMaxWidth = pixmapHeight;
    }
    return imageMaxWidth;
}

void TTilesetView::mousePressEvent(QMouseEvent *event)
{
    emit rowSelected(indexAt(event->pos()).row());
    QTableView::mousePressEvent(event);
}

void TTilesetView::contextMenuEvent(QContextMenuEvent *event)
{
    mContextMenu->popup(event->globalPos());
}

QSize TTilesetView::sizeHint() const
{
    return QSize(240,480);
}
