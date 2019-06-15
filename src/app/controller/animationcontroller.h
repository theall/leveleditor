#ifndef ANIMATIONCONTROLLER_H
#define ANIMATIONCONTROLLER_H

#include "abstractcontroller.h"

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

signals:
    void requestDisplayPropertySheet(TPropertySheet *propertySheet);

private slots:
    void slotOnAnimationListViewIndexPressed(int index);
    void slotOnFrameListViewIndexPressed(int index);

private:
    TAnimationListView *mAnimationListView;
    TFrameListView *mFrameListView;

    void selectAndCenterOn(TObjectItem *objectItem);

private slots:

protected slots:
    void slotTimerEvent() Q_DECL_OVERRIDE;
};

#endif // ANIMATIONCONTROLLER_H
