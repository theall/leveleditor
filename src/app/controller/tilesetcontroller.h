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

private:
    TTilesetTab *mTilesetTab;

    // TAbstractController interface
public:
    bool joint(TMainWindow *mainWindow, TCore *core);
    void setCurrentDocument(TDocument *document);

private slots:
    void slotOnResourceLoadCompleted();

protected slots:
    void slotTimerEvent();
};

#endif // TTILESETCONTROLLER_H
