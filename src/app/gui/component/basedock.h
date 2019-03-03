#ifndef BASEDOCK_H
#define BASEDOCK_H

#include <QDockWidget>

#define CREATE_ACTION(action,image,func) \
    action = new QAction(this);\
    action->setEnabled(false);\
    action->setIcon(QIcon(image));\
    connect(action, SIGNAL(triggered()), this, SLOT(func()))

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
