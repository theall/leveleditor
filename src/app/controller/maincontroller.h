#ifndef TMAINCONTROLLER_H
#define TMAINCONTROLLER_H

#include <QVariant>

#include "tabcontroller.h"
#include "mainpropertycontroller.h"
#include "undocontroller.h"
#include "miniscenecontroller.h"
#include "optionscontroller.h"

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
    void slotRequestSelectRoot(TSelectRootDialog *dialog);
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
    void slotOnProgress(int progress, int total);

private:
    TOptionsController *mOptionsController;
    TTabController *mTabController;
    TMainPropertyController *mMainPropertyController;
    TUndoController *mUndoController;
    TMiniSceneController *mMiniSceneController;

    bool confirmAllSaved();
    void createNewDocument(const QString &projectRoot,
                           const QString &projectName,
                           const QString &projectVersion,
                           const QString &projectAuthor,
                           const QString &projectContact,
                           const QString &projectComment);

protected slots:
    void slotTimerEvent() Q_DECL_OVERRIDE;
};

#endif // TMAINCONTROLLER_H
