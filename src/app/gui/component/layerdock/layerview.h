#ifndef TLAYERVIEW_H
#define TLAYERVIEW_H

#include <QMenu>
#include <QAction>
#include <QTreeView>
#include <QModelIndex>
#include <QKeyEvent>

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

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void slotCurrentRowChanged(const QModelIndex &index);
    void slotPressed(const QModelIndex &index);
    void slotOnSectionResized(int logicalIndex);
    void slotSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

private:
    QAction *mActionAddForeLayer;
    QAction *mActionAddBackLayer;
    QAction *mActionRemoveLayer;

    QAction *mActionDuplicateLayer;
    QAction *mActionMergeLayerDown;
    QAction *mActionMoveLayerUp;
    QAction *mActionMoveLayerDown;
    QAction *mActionToggleOtherLayers;
    QAction *mActionLayerProperties;

    QMenu *mContextMenu;
};

#endif // TLAYERVIEW_H
