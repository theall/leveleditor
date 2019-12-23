#ifndef TCHARACTER_PANEL_CONTROLLER_H
#define TCHARACTER_PANEL_CONTROLLER_H

#include "abstractcontroller.h"

class TCharacterDock;
class TCharacterTab;
class TChunkModel;
class TItemModel;
class TShotModel;
class TCharacterView;
class TItemView;
class TChunkView;
class TShotView;

class TCharacterPanelController : public TAbstractController
{
    Q_OBJECT

public:
    TCharacterPanelController(QObject *parent = 0);
    ~TCharacterPanelController();

private:
    TCharacterDock *mCharacterDock;
    TCharacterTab *mCharacterTab;

private:
     TCharacterView *mCharacter;
     TItemModel *mItemModel;
     TChunkModel *mChunkModel;
     TShotModel *mShotModel;
     int msg;

    // TAbstractController interface
public:
    bool joint(TMainWindow *mainWindow, TCore *core);
    void setCurrentDocument(TDocument *document);
    void setFace();
    void setItem();
    void setShot();
    void setChunk();

private slots:
    void slotOnCoreReady();
    void slotCharacterToggled(int index, bool toggled);

protected slots:
    void slotTimerEvent();
};

#endif // TCHARACTER_PANEL_CONTROLLER_H
