#include "layerdock.h"
#include "layerview.h"

#include <QMenu>
#include <QToolBar>
#include <QBoxLayout>
#include <QContextMenuEvent>

TLayerDock::TLayerDock(QWidget *parent) :
    QDockWidget(parent)
  , mLayerView(new TLayerView(this))
  , mUpdatingSlider(false)
  , mChangingLayerOpacity(false)
{
    setObjectName(QLatin1String("layersDock"));

    QWidget *widget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->setMargin(5);

    QToolBar *buttonContainer = new QToolBar;
    buttonContainer->setFloatable(false);
    buttonContainer->setMovable(false);
    buttonContainer->setIconSize(QSize(16, 16));

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

void TLayerDock::layerChanged(int index)
{
    Q_UNUSED(index);
}

void TLayerDock::editLayerName()
{

}

void TLayerDock::slotSliderValueChanged(int opacity)
{
    Q_UNUSED(opacity);
}

void TLayerDock::retranslateUi()
{
    setWindowTitle(tr("Layers"));
}
