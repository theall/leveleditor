#ifndef TCHARACTER_PANEL_CONTROLLER_H
#define TCHARACTER_PANEL_CONTROLLER_H

#include "abstractcontroller.h"

class TCharacterDock;
class TCharacterPanelController : public TAbstractController
{
    Q_OBJECT

public:
    TCharacterPanelController(QObject *parent = 0);
    ~TCharacterPanelController();

private:
    TCharacterDock *mCharacterDock;

    // TAbstractController interface
public:
    bool joint(TMainWindow *mainWindow, TCore *core);
    void setCurrentDocument(TDocument *document);

private slots:
    void slotOnCoreReady();

protected slots:
    void slotTimerEvent();
};

#endif // TCHARACTER_PANEL_CONTROLLER_H
