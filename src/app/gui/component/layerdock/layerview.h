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
    void selectFirst();
    void selectLast();
    void selectRow(int row);

    QSize sizeHint() const override;
    QList<int> getSelectedRows() const;
    QMenu *contextMenu();

signals:
    void requestRemoveObject(int index);
    void onSelectionChanged(const QList<int> &rows);
    void currentRowChanged(int row);
    //void buttoncurrentRowChanged(int row);
    void requestShowLayers(const QList<int> &rows, bool show);
    void requestLockLayers(const QList<int> &rows, bool lock);

protected:
    void changeEvent(QEvent *e) override;
    void contextMenuEvent(QContextMenuEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void slotCurrentChanged(const QModelIndex &current, const QModelIndex &previours);
    //void slotbuttonCurrentChanged(const QModelIndex &current, const QModelIndex &previours);
    void slotPressed(const QModelIndex &index);
    void slotOnActivated(const QModelIndex &index);
    void slotOnSectionResized(int logicalIndex);
    void slotSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void slotActionShowTriggered(bool);
    void slotActionHideTriggered(bool);
    void slotActionLockTriggered(bool);
    void slotActionUnLockTriggered(bool);

private:
    QAction *mActionShow;
    QAction *mActionHide;
    QAction *mActionLock;
    QAction *mActionUnLock;

    QMenu *mContextMenu;
    void retranslateUi();

    // QAbstractItemView interface
public:
    void setModel(QAbstractItemModel *model);
};

#endif // TLAYERVIEW_H
