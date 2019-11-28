#ifndef ANIMATIONDOCK_H
#define ANIMATIONDOCK_H

#include <QAction>
#include <QToolBar>

#include "container.h"
#include "../basedock.h"
class TAnimationDock : public TBaseDock
{
    Q_OBJECT

public:
    TAnimationDock(QWidget *parent = nullptr);
    ~TAnimationDock();

    TAnimationListView *getAnimationListView() const;
    TFrameListView *getFrameListView() const;

signals:
    void requestAdjustFPS(int fps);

private:
    TContainer *mContainer;

    // TBaseDock interface
public:
    void retranslateUi() Q_DECL_OVERRIDE;
};
#endif // ANIMATIONDOCK_H
