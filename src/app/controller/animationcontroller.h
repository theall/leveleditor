#ifndef ANIMATIONCONTROLLER_H
#define ANIMATIONCONTROLLER_H

#include "abstractcontroller.h"
#include "gui/component/animationdock/container.h"

class TFrame;
class TAnimationDock;
class TAnimationListView;
class TFrameListView;

class TAnimationController : public TAbstractController
{
    Q_OBJECT

public:
    TAnimationController(QObject *parent = 0);
    ~TAnimationController();

    bool joint(TMainWindow *mainWindow, TCore *core) Q_DECL_OVERRIDE;
    void setCurrentDocument(TDocument *document) Q_DECL_OVERRIDE;

    void getCurrentObjectAttribute();

private:
    TFrame *createFrame(TTile *tile,TTileModel *tileModel, int tileIndex, int layerIndex, int Douration=1);
signals:
    void requestDisplayPropertySheet(TPropertySheet *propertySheet);
    void requestAdjustFPS(int fps);
    void requestPlayAnimation();
    void requestStopPlayAnimation();

private slots:
    void slotRequestRemoveFrames(const QList<int> &indexList);
    void slotRequestMoveIndex(const QList<int> &indexList, const Dir &dir);
    void slotOnAnimationListViewIndexPressed(int index);
    void slotOnFrameListViewIndexPressed(int index);
    void slotRequestAddAnimation();
    void slotRequestCopyAnimation();
    void slotRequestAddFrames();

    void slotOnSelectedObjectChanged(TObject *prev, TObject *current);

private:
    TAnimationDock *mAnimationDock;
    TContainer *mContainer;
    TAnimationListView *mAnimationListView;
    TFrameListView *mFrameListView;

    TAnimationModel *getAnimationModel() const;
    void selectAndCenterOn(TObjectItem *objectItem);

private slots:

protected slots:
    void slotTimerEvent() Q_DECL_OVERRIDE;
};

#endif // ANIMATIONCONTROLLER_H
