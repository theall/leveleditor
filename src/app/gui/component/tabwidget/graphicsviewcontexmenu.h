#ifndef TGRAPHICSVIEWCONTEXMENU_H
#define TGRAPHICSVIEWCONTEXMENU_H

#include <QMenu>
#include <QAction>

class TGraphicsViewContextMenu : public QMenu
{
    Q_OBJECT

public:
    explicit TGraphicsViewContextMenu(QWidget *parent = Q_NULLPTR);
    ~TGraphicsViewContextMenu();

    void setActionCloneState(bool state);
    void setActionCopyState(bool state);
    void setActionPasteState(bool state);
    void setActionDeleteState(bool state);
    void setAllActionsState(bool state);

signals:
    void pressDownClone();
    void pressDownCopy();
    void pressDownPaste();
    void pressDownDelete();
    void pressDownTop();
    void pressDownLeft();
    void pressDownRight();
    void pressDownDown();
    void pressDownHorizontal();
    void pressDownVertical();
    void pressDownPlat();
    void pressDownBox();
    void pressDownArea();
    void pressDownDangerArea();
    void pressDownClearHeight();

private slots:
    void slotActionCloneTriggered();
    void slotActionCopyTriggered();
    void slotActionPasteTriggered();
    void slotActionDeleteTriggered();
    void slotActionTopTriggered();
    void slotActionLeftTriggered();
    void slotActionRightTriggered();
    void slotActionDownTriggered();
    void slotActionHorizontalTriggered();
    void slotActionVerticalTriggered();
    void slotActionPlatTriggered();
    void slotActionBoxTriggered();
    void slotActionAreaTriggered();
    void slotActionDangerAreaTriggered();
    void slotActionClearHeightTriggered();
private:
    QAction *mActionClone;
    QAction *mActionCopy;
    QAction *mActionPaste;
    QAction *mActionDelete;
    QAction *mActionTop;
    QAction *mActionLeft;
    QAction *mActionRight;
    QAction *mActionDown;
    QAction *mActionHorizontal;
    QAction *mActionVertical;
    QAction *mActionPlat;
    QAction *mActionBox;
    QAction *mActionArea;
    QAction *mActionDangerArea;
    QAction *mActionClearHeight;
private:
    void retranslateUi();
};

#endif // TGRAPHICSVIEWCONTEXMENU_H
