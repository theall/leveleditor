#ifndef TTILESETTAB_H
#define TTILESETTAB_H

#include <QMenu>
#include <QAction>
#include <QTabWidget>

class TTilesetTab : public QTabWidget
{
    Q_OBJECT

public:
    TTilesetTab(QWidget *parent = nullptr);
    ~TTilesetTab();

    int addTab(void *tileset, const QString &name, const QPixmap &icon=QPixmap());
    int findTileSetIndex(void *tileSet);
    bool removeTab(void *tileSet);
    void *currentTileSet();

    void setTileSetIcon(void *tileSet, const QIcon &icon);

signals:
    // To TTabController
    void requestSwitchToTileSet(void *tileSet);
    void requestCloseTileSet(void *tileSet);

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

private:
    QList<void*> mTileSets;
    QMenu *mContextMenu;
    QAction *mActionAddTiles;
    QAction *mActionAddTileSet;

    void switchTo(int diff);
    void retranslateUi();
};

#endif // TTILESETTAB_H