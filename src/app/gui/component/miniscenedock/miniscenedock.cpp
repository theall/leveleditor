#include "miniscenedock.h"

#include <QEvent>

TMiniSceneDock::TMiniSceneDock(QWidget *parent) :
    TBaseDock(QLatin1String("MiniSceneDock"), parent)
  , mMiniScene(new TMiniSceneFrame(this))
{
    setWidget(mMiniScene);
    retranslateUi();
}

void TMiniSceneDock::changeEvent(QEvent *e)//改变事件
{
    QDockWidget::changeEvent(e);
    switch (e->type()) {//返回事件类型
    case QEvent::LanguageChange://应用程序翻译已更改。
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
