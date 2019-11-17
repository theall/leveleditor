#include "basedock.h"

#include <QEvent>

TBaseDock::TBaseDock(const QString &name, QWidget *parent) :
    QDockWidget(parent)
{
    setFloating(false);
    //此属性保存dock小部件是否浮动。浮动停靠小部件作为其父QMainWindow的“顶部”独立窗口呈现给用户，而不是停靠在QMainWindow中。
    setFeatures(QDockWidget::AllDockWidgetFeatures);
    //（不推荐）dock小部件可以关闭、移动和浮动。由于新功能可能会在将来的版本中添加，因此如果使用此标志，dock小部件的外观和行为可能会更改。请改为指定单个标志。
    setAllowedAreas(Qt::AllDockWidgetAreas);
    //此属性保留可放置停靠小部件的区域。
    setObjectName(name);//此属性保存此对象的名称。
}

TBaseDock::~TBaseDock()
{

}

void TBaseDock::changeEvent(QEvent *event)//改变
{
    if (event->type()==QEvent::LanguageChange)//应用程序翻译已更改。
    {
        retranslateUi();//update ui 更新用户界面
    }

    QDockWidget::changeEvent(event);
}
