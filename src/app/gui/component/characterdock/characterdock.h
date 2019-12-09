#ifndef CHARACTERDOCK_H
#define CHARACTERDOCK_H

#include <QAction>
#include <QToolBar>
#include <QActionGroup>
#include <QStackedWidget>

#include "../basedock.h"
#include "characterview.h"

enum PanelType {
    PA_CHARACTER,
    PA_ITEM,
    PA_SHOT,
    PA_CHUNK,
    PA_TOTAL_COUNT
};

class TCharacterDock : public TBaseDock
{
    Q_OBJECT

public:
    TCharacterDock(QWidget *parent = nullptr);
    ~TCharacterDock();

    TCharacterView *characterView() const;
    TCharacterView *itemView() const;
    TCharacterView *shotView() const;
    TCharacterView *chunkView() const;

    void setPixmapSet(const PanelType &panelType, const QList<QPixmap> &pixmapSet);

private slots:
    void slotActionToggled();

private:
    TCharacterView *mCharacterView;
    TCharacterView *mItemView;
    TCharacterView *mShotView;
    TCharacterView *mChunkView;
    QStackedWidget *mStackedWidget;
    QActionGroup *mActionGroup;

    // TBaseDock interface
public:
    void retranslateUi() Q_DECL_OVERRIDE;
};

#endif // CHARACTERDOCK_H
