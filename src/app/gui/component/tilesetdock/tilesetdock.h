#ifndef TTILESETDOCK_H
#define TTILESETDOCK_H

#include "../basedock.h"
#include "tilesettab.h"
class TTilesetDock : public TBaseDock
{
    Q_OBJECT

public:
    TTilesetDock(QWidget *parent = nullptr);
    ~TTilesetDock();

    TTilesetTab *tilesetTab() const;

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
