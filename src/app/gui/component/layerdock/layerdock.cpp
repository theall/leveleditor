#include "layerdock.h"
#include "layerview.h"

#include <QMenu>
#include <QToolBar>
#include <QBoxLayout>
#include <QContextMenuEvent>

TLayerDock::TLayerDock(QWidget *parent) :
    QDockWidget(parent)
  , mLayerView(new TLayerView(this))
  , mOpacityLabel(new QLabel)
  , mOpacitySlider(new QSlider(Qt::Horizontal))
{
    setObjectName(QLatin1String("LayersDock"));

    QWidget *widget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->setMargin(0);
    connect(mLayerView, SIGNAL(currentRowChanged(int)), this, SLOT(slotCurrentLayerSelected(int)));

    QHBoxLayout *opacityLayout = new QHBoxLayout;
    mOpacitySlider->setRange(0, 100);
    mOpacitySlider->setEnabled(false);
    mOpacityLabel->setBuddy(mOpacitySlider);
    opacityLayout->addWidget(mOpacityLabel);
    opacityLayout->addWidget(mOpacitySlider);
    connect(mOpacitySlider, SIGNAL(valueChanged(int)), this, SLOT(slotSliderValueChanged(int)));

    QToolBar *buttonContainer = new QToolBar;
    buttonContainer->setFloatable(false);
    buttonContainer->setMovable(false);
    buttonContainer->setIconSize(QSize(16, 16));

    mActionShowTiles = new QAction(this);
    mActionShowTiles->setShortcut(tr("Ctrl+Shift+T"));
    mActionShowTiles->setIcon(QIcon(QLatin1String(":/layersdock/images/show_hide_others.png")));

    mActionShowObjects = new QAction(this);
    mActionShowObjects->setShortcut(tr("Ctrl+Shift+O"));
    mActionShowObjects->setIcon(QIcon(QLatin1String(":/layersdock/images/show_hide_others.png")));

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
    listAndToolBar->addLayout(opacityLayout);
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

void TLayerDock::slotSliderValueChanged(int value)
{
    emit layerOpacityChanged(mLayerView->getSelectedRows(), (float)value/100);
}

void TLayerDock::slotCurrentLayerSelected(int row)
{
    mOpacitySlider->setEnabled(row!=-1);
    mOpacityLabel->setEnabled(row!=-1);
}

TLayerView *TLayerDock::layerView() const
{
    return mLayerView;
}

void TLayerDock::setOpacitySliderValue(int value)
{
    mOpacitySlider->blockSignals(true);
    mOpacitySlider->setValue(value);
    mOpacitySlider->blockSignals(false);
}

void TLayerDock::setOpacitySliderValue(qreal value)
{
    mOpacitySlider->blockSignals(true);
    mOpacitySlider->setValue((int)(value*100));
    mOpacitySlider->blockSignals(false);
}

void TLayerDock::retranslateUi()
{
    setWindowTitle(tr("Layers Dock"));

    mOpacityLabel->setText(tr("Opacity:"));
    mActionShowTiles->setToolTip(tr("Show/&Hide all tile Layers"));
    mActionShowObjects->setToolTip(tr("Show/&Hide all object Layers"));
    mActionToggleOther->setToolTip(tr("Show/&Hide all Other Layers"));
    mActionToggleLockOther->setToolTip(tr("Lock/&Unlock all Other Layers"));
}
