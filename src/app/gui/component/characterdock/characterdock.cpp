#include "characterdock.h"

#include <QSplitter>
#include <QVBoxLayout>
#include <QScrollArea>

TCharacterDock::TCharacterDock(QWidget *parent) :
    TBaseDock(QLatin1String("CharacterDock"), parent)
  , mCharacterView(new TCharacterView(this))
{
    CREATE_ACTION_TOGGLED(mActionShowIcon, ":/actionsdock/images/add.png", slotActionShowIconToggled);

    mActionShowIcon->setCheckable(true);

    QToolBar *toolBar = new QToolBar(this);
    toolBar->setFloatable(false);
    toolBar->setMovable(false);
    toolBar->setIconSize(QSize(16, 16));
    toolBar->addAction(mActionShowIcon);

    QScrollArea *container = new QScrollArea(this);
    container->setWidgetResizable(true);

    QVBoxLayout *scrollAreaLayout = new QVBoxLayout(container);
    scrollAreaLayout->setContentsMargins(0, 0, 0, 0);
    scrollAreaLayout->setSpacing(0);
    scrollAreaLayout->addWidget(toolBar);
    scrollAreaLayout->addWidget(mCharacterView);
    setWidget(container);

    retranslateUi();

#ifdef GUI_STAND_ALONE
    for(int i=0;i<45;i++) {
        mCharacterView->add(QPixmap());
    }
#endif
}

TCharacterDock::~TCharacterDock()
{

}

void TCharacterDock::slotActionShowIconToggled(bool toggled)
{
    if(toggled) {

    } else {

    }
}

TCharacterView *TCharacterDock::characterView() const
{
    return mCharacterView;
}

void TCharacterDock::retranslateUi()
{
    setWindowTitle(tr("Character"));
}
