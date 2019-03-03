#include "miniscenedock.h"
#include "miniscene.h"

#include <QEvent>

TMiniSceneDock::TMiniSceneDock(QWidget *parent) :
    TBaseDock(QLatin1String("miniSceneDock"), parent)
  , mMiniScene(new TMiniScene(this))
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

TMiniSceneDock::~TMiniSceneDock()
{

}
