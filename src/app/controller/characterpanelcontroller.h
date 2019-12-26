#ifndef TCHARACTER_PANEL_CONTROLLER_H
#define TCHARACTER_PANEL_CONTROLLER_H

#include "abstractcontroller.h"
#include "../gui/component/characterdock/characterdock.h"

class TChunkModel;
class TItemModel;
class TShotModel;
class TItemView;
class TChunkView;
class TShotView;

class TCharacterPanelController : public TAbstractController
{
    Q_OBJECT

public:
    TCharacterPanelController(QObject *parent = 0);
    ~TCharacterPanelController();

    void setCurrentDocument(TDocument *document);
    void setCharacterEnabled(bool enabled);
    TPixmapId *getCurrentPixmapId() const;

private:
    TCharacterDock *mCharacterDock;

private:
     TItemModel *mItemModel;
     TChunkModel *mChunkModel;
     TShotModel *mShotModel;

    void setFace();
    void setItem();
    void setShot();
    void setChunk();
    
    // TAbstractController interface
public:
    bool joint(TMainWindow *mainWindow, TCore *core);

private slots:
    void slotOnCoreReady();
    void slotButtonPushed(const PanelType &panelType, int index);

protected slots:
    void slotTimerEvent();
};

#endif // TCHARACTER_PANEL_CONTROLLER_H
