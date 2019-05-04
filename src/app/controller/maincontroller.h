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
    void slotRequestOpenProject(const QString &file);
    void slotRequestSaveCurrentProject();
    void slotRequestSaveAllProjects();
    void slotRequestExitApp(bool &approved);
    void slotRequestCloseCurrentProject();
    void slotRequestCloseAllProjects();
    void slotRequestReloadCurrentProject();
    void slotRequestDisplayProjectProperties();
    void slotRequestRunCurrentProject();

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

    bool confirmAllSaved();
    void createNewDocument();

protected slots:
    void slotTimerEvent() Q_DECL_OVERRIDE;
};

#endif // TMAINCONTROLLER_H
