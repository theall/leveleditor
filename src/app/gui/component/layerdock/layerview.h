#ifndef TLAYERVIEW_H
#define TLAYERVIEW_H

#include <QMenu>
#include <QAction>
#include <QTreeView>
#include <QKeyEvent>
#include <QModelIndex>

/**
 * This view makes sure the size hint makes sense and implements the context
 * menu.
 */
class TLayerView : public QTreeView
{
    Q_OBJECT

public:
    explicit TLayerView(QWidget *parent = nullptr);

    void selectRows(QList<int> rows, int newRow);

    QSize sizeHint() const override;

    QMenu *contextMenu();

signals:
    void requestRemoveObject(int index);
    void onSelectionChanged(QList<int> rows);
    void currentRowChanged(int row);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void slotCurrentRowChanged(const QModelIndex &current, const QModelIndex &previours);
    void slotPressed(const QModelIndex &index);
    void slotOnActivated(const QModelIndex &index);
    void slotOnSectionResized(int logicalIndex);
    void slotSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

private:
    QAction *mActionMoveLayerUp;
    QAction *mActionMoveLayerDown;
    QAction *mActionToggleOtherLayers;

    QMenu *mContextMenu;

    // QAbstractItemView interface
public:
    void setModel(QAbstractItemModel *model);
};

#endif // TLAYERVIEW_H
