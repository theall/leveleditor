#ifndef TCHARACTER_PANEL_CONTROLLER_H
#define TCHARACTER_PANEL_CONTROLLER_H

#include "abstractcontroller.h"
class TCharacterView;
class TCharacterPanelController : public TAbstractController
{
    Q_OBJECT

public:
    TCharacterPanelController(QObject *parent = 0);
    ~TCharacterPanelController();

private:
    TCharacterView *mCharacterPanel;

    // TAbstractController interface
public:
    bool joint(TMainWindow *mainWindow, TCore *core);
    void setCurrentDocument(TDocument *document);

private slots:
    void slotOnResourceLoadCompleted();

protected slots:
    void slotTimerEvent();
};

#endif // TCHARACTER_PANEL_CONTROLLER_H
