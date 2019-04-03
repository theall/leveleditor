#include "tilesetview.h"

#include <QMouseEvent>
#include <QHeaderView>
#include <QContextMenuEvent>

TTileSetView::TTileSetView(QWidget *parent) :
    QTableView(parent)
  , mContextMenu(new QMenu(this))
{
    setObjectName(QStringLiteral("TileSetView"));
    setFrameShape(QFrame::Panel);
    setFrameShadow(QFrame::Sunken);

    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::ExtendedSelection);

    horizontalHeader()->setStretchLastSection(true);
    horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    horizontalHeader()->setVisible(false);
    verticalHeader()->setVisible(false);

    setSortingEnabled(false);
    setShowGrid(true);

    mActionAddTiles = mContextMenu->addAction(QString(), this, SLOT(slotActionAddTilesTriggered()));
    mActionRemoveTiles = mContextMenu->addAction(QString(), this, SLOT(slotActionRemoveTilesTriggered()));
    mContextMenu->addSeparator();
    mActionShowGrid = mContextMenu->addAction(QString(), this, SLOT(slotActionShowGridTriggered(bool)));

    retranslateUi();
}

TTileSetView::~TTileSetView()
{

}

QList<int> TTileSetView::getSelectedIndexes()
{
    QSet<int> selectedRows;
    for(QModelIndex index : selectionModel()->selectedIndexes())
    {
        selectedRows.insert(index.row());
    }
    return selectedRows.toList();
}

int TTileSetView::currentRow()
{
    return currentIndex().row();
}

void TTileSetView::selectRow(int row)
{
    if(model())
    {
        QTableView::selectRow(row);
        emit rowSelected(row);
    }
}

int TTileSetView::rowCount()
{
    QAbstractItemModel *m = model();
    return m?m->rowCount():0;
}

void TTileSetView::slotActionShowGridTriggered(bool checked)
{
    setShowGrid(checked);
}

void TTileSetView::slotActionAddTilesTriggered()
{

}

void TTileSetView::slotActionRemoveTilesTriggered()
{

}

void TTileSetView::slotActionRenameTriggered()
{

}

void TTileSetView::slotSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(selected);
    Q_UNUSED(deselected);

    emit hasSelectionChanged(getSelectedIndexes().size()>0);
}

void TTileSetView::retranslateUi()
{
    mActionAddTiles->setText(tr("Add tiles"));
    mActionRemoveTiles->setText(tr("Remove tiles"));
    mActionShowGrid->setText("Show grid");
}

void TTileSetView::setModel(QAbstractItemModel *model)
{
    QTableView::setModel(model);
    emit validChanged(model!=nullptr);

    if(model)
    {
        connect(selectionModel(),
                SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                this,
                SLOT(slotSelectionChanged(QItemSelection,QItemSelection)));
    }
}

void TTileSetView::mousePressEvent(QMouseEvent *event)
{
    emit rowSelected(indexAt(event->pos()).row());
    QTableView::mousePressEvent(event);
}

void TTileSetView::contextMenuEvent(QContextMenuEvent *event)
{
    mContextMenu->popup(event->globalPos());
}
