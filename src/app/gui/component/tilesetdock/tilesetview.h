#ifndef SOUNDSETVIEW_H
#define SOUNDSETVIEW_H

#include <QMenu>
#include <QAction>
#include <QTableView>

class TTilesetView : public QTableView
{
    Q_OBJECT

public:
    TTilesetView(QWidget *parent=nullptr);
    ~TTilesetView();

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
    void slotActionShowGridTriggered(bool checked);
    void slotActionAddTilesTriggered();
    void slotActionRemoveTilesTriggered();
    void slotActionRenameTriggered();
    void slotSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

private:
    QMenu *mContextMenu;
    QAction *mActionAddTiles;
    QAction *mActionRemoveTiles;
    QAction *mActionShowGrid;

    void retranslateUi();

    // QAbstractItemView interface
public:
    void setModel(QAbstractItemModel *model) Q_DECL_OVERRIDE;
    int sizeHintForRow(int row) const;
    int sizeHintForColumn(int column) const;

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;

    // QWidget interface
public:
    QSize sizeHint() const;
};
#endif // SOUNDSETVIEW_H
