#include "boldcurrentitemdelegate.h"

TBoldCurrentItemDelegate::TBoldCurrentItemDelegate(QItemSelectionModel *selectionModel, QObject *parent) :
    QStyledItemDelegate(parent)
  , mSelectionModel(selectionModel)
{}

void TBoldCurrentItemDelegate::initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const
{
    QStyledItemDelegate::initStyleOption(option, index);

    const QModelIndex current = mSelectionModel->currentIndex();
    if (index.parent() == current.parent() && index.row() == current.row())
        option->font.setBold(true);
}
