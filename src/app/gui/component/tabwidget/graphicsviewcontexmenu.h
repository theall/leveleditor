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

private slots:
    void slotActionCloneTriggered();
    void slotActionCopyTriggered();
    void slotActionPasteTriggered();
    void slotActionDeleteTriggered();

private:
    QAction *mActionClone;
    QAction *mActionCopy;
    QAction *mActionPaste;
    QAction *mActionDelete;

private:
    void retranslateUi();
};

#endif // TGRAPHICSVIEWCONTEXMENU_H
