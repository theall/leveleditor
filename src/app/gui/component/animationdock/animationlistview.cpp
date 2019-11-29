#include "animationlistview.h"

#include <QHeaderView>
#include <QMouseEvent>

TAnimationListView::TAnimationListView(QWidget *parent) :
    QTableView(parent)
  , mContextMenu(new QMenu(this))
{
    setObjectName(QStringLiteral("AnimationListView"));
    setFrameShape(QFrame::Panel);
    setFrameShadow(QFrame::Sunken);

    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);

    horizontalHeader()->setStretchLastSection(true);
    horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    horizontalHeader()->setVisible(false);
    verticalHeader()->setVisible(false);

    setSortingEnabled(false);
    setShowGrid(true);

    mActionRename = mContextMenu->addAction(QString(), this, SLOT(slotActionRenameTriggered()));
    mActionClone = mContextMenu->addAction(QString(), this, SLOT(slotActionCloneTriggered()));
    mActionCopy = mContextMenu->addAction(QString(), this, SLOT(slotActionCopyTriggered()));
    mActionRemove = mContextMenu->addAction(QString(), this, SLOT(slotActionRemoveTriggered()));
    mContextMenu->addSeparator();
    mActionShowGrid = mContextMenu->addAction(QString(), this, SLOT(slotActionShowGridTriggered(bool)));
    mActionHideColumn = mContextMenu->addAction(QString(), this, SLOT(slotActionHideColumnTriggered(bool)));

    mActionShowGrid->setCheckable(true);
    mActionHideColumn->setCheckable(true);
    retranslateUi();
}

TAnimationListView::~TAnimationListView()
{

}

QList<int> TAnimationListView::getSelectedIndexes()
{
    QSet<int> selectedRows;
    for(QModelIndex index : selectionModel()->selectedIndexes())
    {
        selectedRows.insert(index.row());
    }
    return selectedRows.toList();
}

int TAnimationListView::currentRow()
{
    return currentIndex().row();
}

void TAnimationListView::selectRow(int row)
{
    if(model())
    {
        QTableView::selectRow(row);
        emit indexSelected(row);
    }
}

int TAnimationListView::rowCount()
{
    QAbstractItemModel *m = model();
    return m?m->rowCount():0;
}

void TAnimationListView::slotActionRemoveTriggered()
{

}

void TAnimationListView::slotActionShowGridTriggered(bool checked)
{
    setShowGrid(checked);
}

void TAnimationListView::slotActionHideColumnTriggered(bool checked)
{
    if(checked)
        horizontalHeader()->hideSection(0);
    else
        horizontalHeader()->showSection(0);
}

void TAnimationListView::slotActionCloneTriggered()
{

}

void TAnimationListView::slotActionCopyTriggered()
{

}

void TAnimationListView::slotActionRenameTriggered()
{
    edit(currentIndex());
}

void TAnimationListView::retranslateUi()
{
    mActionHideColumn->setText(tr("Hide column"));
    mActionRename->setText(tr("Rename"));
    mActionCopy->setText(tr("Copy"));
    mActionRemove->setText(tr("Remove"));
    mActionClone->setText(tr("Clone"));
    mActionShowGrid->setText(tr("Show grid"));
}

void TAnimationListView::setModel(QAbstractItemModel *model)
{
    QTableView::setModel(model);
}

void TAnimationListView::mousePressEvent(QMouseEvent *event)
{
    QTableView::mousePressEvent(event);
    int row = indexAt(event->pos()).row();
    if(row != -1)
        emit indexPressed(row);
}

void TAnimationListView::contextMenuEvent(QContextMenuEvent *event)
{
    mContextMenu->popup(event->globalPos());
}
