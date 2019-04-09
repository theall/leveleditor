#include "miniscenedock.h"

#include <QEvent>

TMiniSceneDock::TMiniSceneDock(QWidget *parent) :
    TBaseDock(QLatin1String("MiniSceneDock"), parent)
  , mMiniScene(new TMiniSceneFrame(this))
{
    setWidget(mMiniScene);
    retranslateUi();
}

void TMiniSceneDock::changeEvent(QEvent *e)
{
    QDockWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi();
        break;
    default:
        break;
    }
}

void TMiniSceneDock::retranslateUi()
{
    setWindowTitle(tr("Miniscene"));
}

TMiniSceneFrame *TMiniSceneDock::miniScene() const
{
    return mMiniScene;
}

TMiniSceneDock::~TMiniSceneDock()
{

}
