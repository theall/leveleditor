#include "animationdock.h"

TAnimationDock::TAnimationDock(QWidget *parent) :
    TBaseDock(QLatin1String("AnimationDock"), parent)
  , mContainer(new TContainer(this))
{
    setWidget(mContainer);
    retranslateUi();
}

TAnimationDock::~TAnimationDock()
{

}

TAnimationListView *TAnimationDock::getAnimationListView() const
{
    return mContainer->getAnimationListView();
}

TFrameListView *TAnimationDock::getFrameListView() const
{
    return mContainer->getFrameListView();
}

void TAnimationDock::retranslateUi()
{
    setWindowTitle(tr("Animation"));
}

