#ifndef TOBJECTCONTROLLER_H
#define TOBJECTCONTROLLER_H

#include "abstractcontroller.h"

#include "../core/document/model/scenemodel.h"

class TObjectDock;
class TObjectContainer;
class TObjectListView;
class TSubControlObjectListView;

class TObjectController : public TAbstractController
{
    Q_OBJECT

public:
    explicit TObjectController(QObject *parent = 0);
    ~TObjectController();

    bool joint(TMainWindow *mainWindow, TCore *core) Q_DECL_OVERRIDE;
    void setCurrentDocument(TDocument *document) Q_DECL_OVERRIDE;

    void setObjectListViewModel(TBaseModel *baseModel);
    void setSubControlObjectListViewModel(TBaseModel *baseModel);

private slots:

    // From graphics scene
    void slotOnSelectedObjectChanged(TObject *prev, TObject *current);

    //From TObjectListView
    void slotObjectIndexPressed(const QModelIndex &index);

protected slots:
    void slotTimerEvent();

private:
    TSceneModel *mSceneModel;
    TObjectListView *mObjectListView;
    TSubControlObjectListView *mSubControlObjectListView;

private:
    void selectAndCenterOn(TObject *object);

};

#endif // TOBJECTCONTROLLER_H
