#ifndef TTILESETCONTROLLER_H
#define TTILESETCONTROLLER_H

#include "abstractcontroller.h"
class TTilesetTab;
class TTilesetController : public TAbstractController
{
    Q_OBJECT

public:
    TTilesetController(QObject *parent = 0);
    ~TTilesetController();

    void setTilesetEnabled(bool enabled);

private:
    TTilesetTab *mTilesetTab;

    // TAbstractController interface
public:
    bool joint(TMainWindow *mainWindow, TCore *core);
    void setCurrentDocument(TDocument *document);

private slots:
    // From assets load
    void slotOnCoreReady();

    // From tileset view
    void slotOnTilesetViewCurrentRowChanged(int tileset, int row);

    // From graphics scene
    void slotOnSelectedObjectChanged(TObject *prev, TObject *current);

protected slots:
    void slotTimerEvent();
};

#endif // TTILESETCONTROLLER_H
