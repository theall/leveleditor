#ifndef CHARACTERDOCK_H
#define CHARACTERDOCK_H

#include <QAction>
#include <QToolBar>

#include "../basedock.h"
#include "characterview.h"

class TCharacterDock : public TBaseDock
{
    Q_OBJECT

public:
    TCharacterDock(QWidget *parent = nullptr);
    ~TCharacterDock();

    TCharacterView *characterView() const;

private slots:
    void slotActionShowIconToggled(bool);

private:
    QAction *mActionShowIcon;
    TCharacterView *mCharacterView;

    // TBaseDock interface
public:
    void retranslateUi() Q_DECL_OVERRIDE;
};

#endif // CHARACTERDOCK_H
