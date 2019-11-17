#ifndef BASEDOCK_H
#define BASEDOCK_H

#include <QEvent>
#include <QDockWidget>
 //此属性保留操作是否已启用。例如，它们可能只使用灰色阴影显示。
//此属性保存操作的图标。在工具栏中，图标用作工具按钮图标；在菜单中，它显示在菜单文本的左侧没有默认图标。
#define CREATE_ACTION(action,image,func) \
    action = new QAction(this);\
    action->setEnabled(false);\
    action->setIcon(QIcon(image));\
    connect(action, SIGNAL(triggered()), this, SLOT(func()))

#define CREATE_ACTION_TOGGLED(action,image,func) \
    action = new QAction(this);\
    action->setCheckable(true);\
    action->setIcon(QIcon(image));\
    connect(action, SIGNAL(toggled(bool)), this, SLOT(func(bool)))

class TBaseDock : public QDockWidget//浮动窗口
{
public:
    TBaseDock(const QString &name, QWidget *parent = nullptr);
    ~TBaseDock();

    virtual void retranslateUi() = 0;//虚函数

    // QWidget interface QWidget接口
protected:
    void changeEvent(QEvent *) Q_DECL_OVERRIDE;
};

#endif // BASEDOCK_H
