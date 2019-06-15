#include "basedock.h"

#include <QEvent>

TBaseDock::TBaseDock(const QString &name, QWidget *parent) :
    QDockWidget(parent)
{
    setFloating(false);
    setFeatures(QDockWidget::AllDockWidgetFeatures);
    setAllowedAreas(Qt::AllDockWidgetAreas);
    setObjectName(name);
}

TBaseDock::~TBaseDock()
{

}

void TBaseDock::changeEvent(QEvent *event)
{
    if (event->type()==QEvent::LanguageChange)
    {
        retranslateUi();//update ui
    }

    QDockWidget::changeEvent(event);
}
