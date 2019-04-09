#include "characterdock.h"

#include <QSplitter>
#include <QVBoxLayout>

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

    QWidget *container = new QWidget(this);
    QSplitter *splitter = new QSplitter(this);
    splitter->setOrientation(Qt::Vertical);
    splitter->addWidget(mCharacterView);
    QVBoxLayout *vBoxLayout = new QVBoxLayout;
    vBoxLayout->setContentsMargins(5, 5, 5, 5);
    vBoxLayout->setSpacing(0);
    vBoxLayout->addWidget(toolBar);
    vBoxLayout->addWidget(splitter);
    container->setLayout(vBoxLayout);
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

void TCharacterDock::retranslateUi()
{
    setWindowTitle(tr("Character"));
}
