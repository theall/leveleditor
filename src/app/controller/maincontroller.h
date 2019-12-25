#ifndef TMAINCONTROLLER_H
#define TMAINCONTROLLER_H

#include <QVariant>

#include "tabcontroller.h"
#include "mainpropertycontroller.h"
#include "undocontroller.h"
#include "miniscenecontroller.h"
#include "optionscontroller.h"
#include "tilesetcontroller.h"
#include "characterpanelcontroller.h"
#include "mapsdockcontroller.h"
#include "layerscontroller.h"
#include "animationcontroller.h"
#include "objectController.h"

class TMainController : public TAbstractController
{
    Q_OBJECT

public:
    explicit TMainController(QObject *parent = 0);
    ~TMainController();

    bool joint(TMainWindow *mainWindow, TCore *core) Q_DECL_OVERRIDE;
    void setCurrentDocument(TDocument *document) Q_DECL_OVERRIDE;

signals:

private slots:
    // From TMainWindow
    void slotRequestOpenMap(const QString &file);
    void slotRequestCreateNewMap();
    void slotRequestSaveCurrentMap();
    void slotRequestSaveAllMaps();
    void slotRequestExitApp(bool &approved);
    void slotRequestCloseCurrentMap();
    void slotRequestCloseAllMaps();
    void slotRequestReloadCurrentMap();
    void slotRequestDisplayMapProperties();
    void slotRequestRunCurrentMap();
    void slotRequestMoveState(bool idChecked, bool &result);
    void slotRequestShowBorder(bool show);
    void slotOnActionSelectPushed();
    void slotOnActionInsertPushed();

    // From TTabController
    void slotRequestCloseDocument(TDocument *document);
    void slotRequestSwitchToDocument(TDocument *document);
    void slotDocumentDirtyFlagChanged(TDocument *document, bool isDirty);

    // From TPropertyController
    void slotPropertyItemValueChanged(TPropertyItem *propertyItem, const QVariant &newValue);
    void slotPropertyItemActived(TPropertyItem *propertyItem);

    // From assets loader
    void slotOnResourceLoadProgress(int progress, int total);

    // From TMapsDockController
    void slotRequestOpenMap(TMap *map);

    // From TLayersController
    void slotOnLayerSelected(int index);

    // From document
    void slotOnDirtyFlagChanged(bool isDirty);
    void slotOnEditModeChanged(const EditMode &current, const EditMode &prev);

    // From TAnimationController
    void slotRequestDisplayPropertySheet(TPropertySheet *propertySheet);
    void slotRequestAdjustFPS(int fps);
    void slotRequestPlayAnimation();
    void slotRequestStopPlayAnimation();

private:
    TOptionsController *mOptionsController;
    TTabController *mTabController;
    TMainPropertyController *mMainPropertyController;
    TUndoController *mUndoController;
    TMiniSceneController *mMiniSceneController;
    TTilesetController *mTilesetController;
    TCharacterPanelController *mCharacterController;
    TMapsDockController *mMapsDockController;
    TLayersController *mLayersController;
    TAnimationController *mAnimationController;
    TObjectController *mObjectController;

    bool confirmAllSaved();
    void createNewDocument(const QString &moduleName, const TMap::Type &mapType, int mapId);

protected slots:
    void slotTimerEvent() Q_DECL_OVERRIDE;
};

#endif // TMAINCONTROLLER_H
