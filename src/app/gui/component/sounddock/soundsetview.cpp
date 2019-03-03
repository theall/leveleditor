#include "soundsetview.h"

#include <QMouseEvent>
#include <QHeaderView>
#include <QContextMenuEvent>

TSoundSetView::TSoundSetView(QWidget *parent) :
    QTableView(parent)
  , mContextMenu(new QMenu(this))
{
    setObjectName(QStringLiteral("actionsView"));
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

    mActionClone = mContextMenu->addAction(QString(), this, SLOT(slotActionCloneTriggered()));
    mActionCopy = mContextMenu->addAction(QString(), this, SLOT(slotActionCopyTriggered()));
    mActionRemove = mContextMenu->addAction(QString(), this, SLOT(slotActionRemoveTriggered()));
    // mContextMenu->addSeparator();
    // mActionShowGrid = mContextMenu->addAction(QString(), this, SLOT(slotActionShowGridTriggered(bool)));

    retranslateUi();
}

TSoundSetView::~TSoundSetView()
{

}

QList<int> TSoundSetView::getSelectedIndexes()
{
    QSet<int> selectedRows;
    for(QModelIndex index : selectionModel()->selectedIndexes())
    {
        selectedRows.insert(index.row());
    }
    return selectedRows.toList();
}

int TSoundSetView::currentRow()
{
    return currentIndex().row();
}

void TSoundSetView::selectRow(int row)
{
    if(model())
    {
        QTableView::selectRow(row);
        emit rowSelected(row);
    }
}

int TSoundSetView::rowCount()
{
    QAbstractItemModel *m = model();
    return m?m->rowCount():0;
}

void TSoundSetView::slotActionRemoveTriggered()
{

}

void TSoundSetView::slotActionShowGridTriggered(bool checked)
{
    setShowGrid(checked);
}

void TSoundSetView::slotActionCloneTriggered()
{

}

void TSoundSetView::slotActionCopyTriggered()
{

}

void TSoundSetView::slotActionRenameTriggered()
{
    edit(currentIndex());
}

void TSoundSetView::slotSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(selected);
    Q_UNUSED(deselected);

    emit hasSelectionChanged(getSelectedIndexes().size()>0);
}

void TSoundSetView::retranslateUi()
{
    mActionCopy->setText(tr("Copy"));
    mActionRemove->setText(tr("Remove"));
    mActionClone->setText(tr("Clone"));
    // mActionShowGrid->setText(tr("Show grid"));
}

void TSoundSetView::setModel(QAbstractItemModel *model)
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

void TSoundSetView::mousePressEvent(QMouseEvent *event)
{
    emit rowSelected(indexAt(event->pos()).row());
    QTableView::mousePressEvent(event);
}

void TSoundSetView::contextMenuEvent(QContextMenuEvent *event)
{
    mContextMenu->popup(event->globalPos());
}
