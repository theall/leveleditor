#ifndef TGRAPHICSVIEWCONTEXMENU_H
#define TGRAPHICSVIEWCONTEXMENU_H

#include <QMenu>
#include <QAction>

class TGraphicsViewContexMenu : public QMenu
{
public:
    explicit TGraphicsViewContexMenu(QWidget *parent = Q_NULLPTR);
    ~TGraphicsViewContexMenu();

public:
    QAction *actionClone;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionDelete;
    QAction *actionSetAsStamp;

private:
    void retranslateUi();
};

#endif // TGRAPHICSVIEWCONTEXMENU_H
