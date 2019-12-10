#ifndef TOBJECTCONTROLLER_H
#define TOBJECTCONTROLLER_H

#include "abstractcontroller.h"

#include "../core/document/model/scenemodel.h"

class TObjectDock;
class TObjectcontainer;
class TObjectListView;

class TObjectController : public TAbstractController
{
    Q_OBJECT

public:
    explicit TObjectController(QObject *parent = 0);
    ~TObjectController();

    bool joint(TMainWindow *mainWindow, TCore *core) Q_DECL_OVERRIDE;
    void setCurrentDocument(TDocument *document) Q_DECL_OVERRIDE;

    void setObjectModel(TBaseModel *baseModel);

protected slots:
    void slotTimerEvent();

private:
    TSceneModel *mSceneModel;
    TObjectListView *mObjectListView;
};

#endif // TOBJECTCONTROLLER_H
