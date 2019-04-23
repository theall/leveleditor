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

    QHBoxLayout *opacityLayout = new QHBoxLayout;
    opacityLayout->addWidget(mOpacityLabel);
    opacityLayout->addWidget(mOpacitySlider);
    mOpacityLabel->setBuddy(mOpacitySlider);

    const QIcon newIcon(QLatin1String(":/images/16x16/document-new.png"));
    QToolButton *newLayerButton = new QToolButton;
    newLayerButton->setPopupMode(QToolButton::InstantPopup);
    newLayerButton->setMenu(newLayerMenu);
    newLayerButton->setIcon(newIcon);

    QToolBar *buttonContainer = new QToolBar;
    buttonContainer->setFloatable(false);
    buttonContainer->setMovable(false);
    buttonContainer->setIconSize(QSize(16, 16));

    buttonContainer->addWidget(newLayerButton);
//    buttonContainer->addAction(handler->actionMoveLayerUp());
//    buttonContainer->addAction(handler->actionMoveLayerDown());
//    buttonContainer->addAction(handler->actionDuplicateLayer());
//    buttonContainer->addAction(handler->actionRemoveLayer());
//    buttonContainer->addSeparator();
//    buttonContainer->addAction(handler->actionToggleOtherLayers());

    QVBoxLayout *listAndToolBar = new QVBoxLayout;
    listAndToolBar->setSpacing(0);
    listAndToolBar->addWidget(mLayerView);
    listAndToolBar->addWidget(buttonContainer);

    layout->addLayout(opacityLayout);
    layout->addLayout(listAndToolBar);

    setWidget(widget);
    retranslateUi();

    connect(mOpacitySlider, SIGNAL(valueChanged(int)), this, SIGNAL(opacitySliderValueChanged(int)));
}

TLayerDock::~TLayerDock()
{

}

void TLayerDock::enableOpacitySlider(bool enabled)
{
    mOpacityLabel->setEnabled(enabled);
    mOpacitySlider->setEnabled(enabled);
}

void TLayerDock::setOpacitySliderValue(int value)
{
    if(!mOpacitySlider->isEnabled())
        mOpacitySlider->setEnabled(true);

    if(!mOpacitySlider->isEnabled())
        mOpacitySlider->setEnabled(true);

    mOpacitySlider->blockSignals(true);
    mOpacitySlider->setValue(value);
    mOpacitySlider->blockSignals(false);
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
    mOpacityLabel->setText(tr("Opacity:"));
}
