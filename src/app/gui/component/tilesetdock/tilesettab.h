#ifndef TTILESETTAB_H
#define TTILESETTAB_H

#include <QMenu>
#include <QAction>
#include <QTabWidget>
#include <QAbstractItemModel>

class TTilesetTab : public QTabWidget
{
    Q_OBJECT

public:
    explicit TTilesetTab(QWidget *parent = nullptr);
    ~TTilesetTab();

    int addTab(QAbstractItemModel *tilesetModel, const QString &name, const QPixmap &icon=QPixmap());
    int findTilesetIndex(void *tileSet);
    bool removeTab(void *tileSet);
    void *currentTileset();

    void setTilesetIcon(void *tileSet, const QIcon &icon);

signals:
    // To TTilesetController
    void onTilesetViewRowChanged(int tabIndex, int row);

    // To TTabController
    void requestSwitchToTileset(void *tileSet);
    void requestCloseTileset(void *tileSet);

    // To main window
    void onTabCountChanged(int count);
    void onActionSaveTriggered();

private slots:
    void slotOnCurrentIndexChanged(int index);
    void slotSwitchToLeft();
    void slotSwitchToRight();
    void slotCustomContextMenuRequested(const QPoint &pos);
    void slotActionAddTilesTriggered();
    void slotActionRemoveTilesTriggered();
    void slotOnTilesetRowChanged(int row);

private:
    QList<void*> mTilesets;
    QMenu *mContextMenu;
    QAction *mActionAddTiles;
    QAction *mActionAddTileset;

    void switchTo(int diff);
    void retranslateUi();
};

#endif // TTILESETTAB_H
