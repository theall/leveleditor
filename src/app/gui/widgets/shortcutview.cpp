#include "shortcutview.h"

#include <QAction>
#include <QHeaderView>
#include <QStandardItem>
#include <QStandardItemModel>

TShortcutView::TShortcutView(QWidget *parent) :
    QTreeView(parent)
{
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    header()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

TShortcutView::~TShortcutView()
{

}

void TShortcutView::slotCurrentSelectionChanged(QModelIndex current, QModelIndex previous)
{
    Q_UNUSED(previous)

    QStandardItem *item = ((QStandardItemModel*)model())->item(current.row(), 1);
    if(item)
    {
        QAction *action = item->data().value<QAction*>();
        if(action)
            emit onActionSelected(action);
    }
}

void TShortcutView::setModel(QAbstractItemModel *model)
{
    QTreeView::setModel(model);

    connect(selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex, QModelIndex)),
            this,
            SLOT(slotCurrentSelectionChanged(QModelIndex, QModelIndex)));
}
