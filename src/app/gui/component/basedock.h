#ifndef BASEDOCK_H
#define BASEDOCK_H

#include <QEvent>
#include <QDockWidget>

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

class TBaseDock : public QDockWidget
{
public:
    TBaseDock(const QString &name, QWidget *parent = nullptr);
    ~TBaseDock();

    virtual void retranslateUi() = 0;

    // QWidget interface
protected:
    void changeEvent(QEvent *) Q_DECL_OVERRIDE;
};

#endif // BASEDOCK_H
