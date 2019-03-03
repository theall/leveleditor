#ifndef SOUNDSETVIEW_H
#define SOUNDSETVIEW_H

#include <QMenu>
#include <QAction>
#include <QTableView>

class TSoundSetView : public QTableView
{
    Q_OBJECT

public:
    TSoundSetView(QWidget *parent=nullptr);
    ~TSoundSetView();

    QList<int> getSelectedIndexes();
    int currentRow();
    void selectRow(int row);
    int rowCount();

signals:
    // To controller
    void rowSelected(int row);

    // To gui
    void validChanged(bool valid);
    void hasSelectionChanged(bool hasSelection);

private slots:
    void slotActionRemoveTriggered();
    void slotActionShowGridTriggered(bool checked);
    void slotActionCloneTriggered();
    void slotActionCopyTriggered();
    void slotActionRenameTriggered();
    void slotSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

private:
    QMenu *mContextMenu;
    QAction *mActionCopy;
    QAction *mActionRemove;
    QAction *mActionClone;
    QAction *mActionShowGrid;

    void retranslateUi();

    // QAbstractItemView interface
public:
    void setModel(QAbstractItemModel *model) Q_DECL_OVERRIDE;

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;
};
#endif // SOUNDSETVIEW_H
