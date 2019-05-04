#ifndef TBOLDCURRENTITEMDELEGATE_H
#define TBOLDCURRENTITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QItemSelectionModel>

class TBoldCurrentItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit TBoldCurrentItemDelegate(QItemSelectionModel *selectionModel,
                                     QObject *parent = nullptr);

    // QStyledItemDelegate interface
protected:
    void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const override;

private:
    QItemSelectionModel *mSelectionModel;
};

#endif // TBOLDCURRENTITEMDELEGATE_H
