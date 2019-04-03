#ifndef TTILESETDOCK_H
#define TTILESETDOCK_H

#include "../basedock.h"
#include "tilesettab.h"
class TTileSetDock : public TBaseDock
{
    Q_OBJECT

public:
    TTileSetDock(QWidget *parent = nullptr);
    ~TTileSetDock();

protected:
    void changeEvent(QEvent *e) override;

private slots:
    void slotAddTilesetTriggered();
    void slotRemoveTilesetTriggered();

private:
    TTilesetTab *mTilesetTab;
    QAction *mActionAddTileset;
    QAction *mActionRemoveTileset;
    void retranslateUi();
};


#endif // TTILESETDOCK_H
