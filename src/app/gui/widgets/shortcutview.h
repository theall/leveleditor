#ifndef TSHORTCUTVIEW_H
#define TSHORTCUTVIEW_H

#include <QTreeView>

class TShortcutView : public QTreeView
{
    Q_OBJECT

public:
    TShortcutView(QWidget *parent = 0);
    ~TShortcutView();

    void setModel(QAbstractItemModel *model) Q_DECL_OVERRIDE;

signals:
    void onActionSelected(QAction *);

private slots:
    void slotCurrentSelectionChanged(QModelIndex current, QModelIndex previous);
};

#endif // TSHORTCUTVIEW_H
