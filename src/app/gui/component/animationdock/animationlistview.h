#ifndef ANIMATIONLISTVIEW_H
#define ANIMATIONLISTVIEW_H

#include <QMenu>
#include <QAction>
#include <QTableView>

class TAnimationListView : public QTableView
{
    Q_OBJECT

public:
    TAnimationListView(QWidget *parent=nullptr);
    ~TAnimationListView();

    QList<int> getSelectedIndexes();
    int currentRow();
    void selectRow(int row);
    int rowCount();

signals:
    void indexPressed(int row);
    void indexSelected(int row);

private slots:
    void slotActionRemoveTriggered();
    void slotActionShowGridTriggered(bool checked);
    void slotActionHideColumnTriggered(bool checked);
    void slotActionCloneTriggered();
    void slotActionCopyTriggered();
    void slotActionRenameTriggered();

private:
    QMenu *mContextMenu;
    QAction *mActionHideColumn;
    QAction *mActionRename;
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

#endif // ANIMATIONLISTVIEW_H
