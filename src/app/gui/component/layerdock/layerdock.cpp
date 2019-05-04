#include "layerdock.h"
#include "layerview.h"

#include <QMenu>
#include <QToolBar>
#include <QBoxLayout>
#include <QContextMenuEvent>

TLayerDock::TLayerDock(QWidget *parent) :
    QDockWidget(parent)
  , mLayerView(new TLayerView(this))
{
    setObjectName(QLatin1String("LayersDock"));

    QWidget *widget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->setMargin(0);

    QToolBar *buttonContainer = new QToolBar;
    buttonContainer->setFloatable(false);
    buttonContainer->setMovable(false);
    buttonContainer->setIconSize(QSize(16, 16));

    mActionToggleOther = new QAction(this);
    mActionToggleOther->setShortcut(tr("Ctrl+Shift+H"));
    mActionToggleOther->setIcon(QIcon(QLatin1String(":/layersdock/images/show_hide_others.png")));

    mActionToggleLockOther = new QAction(this);
    mActionToggleLockOther->setShortcut(tr("Ctrl+Shift+L"));
    mActionToggleLockOther->setIcon(QIcon(QLatin1String(":/layersdock/images/locked.png")));

    buttonContainer->addAction(mActionToggleOther);
    buttonContainer->addAction(mActionToggleLockOther);

    QVBoxLayout *listAndToolBar = new QVBoxLayout;
    listAndToolBar->setSpacing(0);
    listAndToolBar->addWidget(mLayerView);
    listAndToolBar->addWidget(buttonContainer);
    layout->addLayout(listAndToolBar);

    setWidget(widget);
    retranslateUi();
}

TLayerDock::~TLayerDock()
{

}

void TLayerDock::changeEvent(QEvent *e)
{
    QDockWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi();
        break;
    default:
        break;
    }
}

TLayerView *TLayerDock::layerView() const
{
    return mLayerView;
}

void TLayerDock::retranslateUi()
{
    setWindowTitle(tr("Layers Dock"));

    mActionToggleOther->setToolTip(tr("Show/&Hide all Other Layers"));
    mActionToggleLockOther->setToolTip(tr("Lock/&Unlock all Other Layers"));
}
