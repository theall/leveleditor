#ifndef TOBJECTCONTROLLER_H
#define TOBJECTCONTROLLER_H

#include "abstractcontroller.h"

#include "../core/document/model/scenemodel.h"
#include "../core/document/model/enemymodel.h"

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

    void resetCurrentModel();
    void setObjectListViewModel(TBaseModel *baseModel);
    void setSubControlObjectListViewModel(TEnemyModel *enemyModel);

private slots:
    // From graphics scene
    void slotOnSelectedObjectChanged(TObject *prev, TObject *current);

    //From TObjectListView
    void slotObjectIndexPressed(const QModelIndex &index);

    //From TSubControlobjectListView
    void slotEnemyIndexPressed(int index);

protected slots:
    void slotTimerEvent();

private:
    TSceneModel *mSceneModel;
    TObjectListView *mObjectListView;
    TSubControlObjectListView *mSubControlObjectListView;

private:
    void selectAndCenterOn(TObjectList &objectList);

};

#endif // TOBJECTCONTROLLER_H
