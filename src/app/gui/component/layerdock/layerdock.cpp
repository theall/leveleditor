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
  , mOpacitySlider(new QSlider(Qt::Horizontal))//提供滑块（水平）
{
    setObjectName(QLatin1String("LayersDock"));//保存此对象的名称

    QWidget *widget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(widget);//垂直排列
    layout->setMargin(0);//设置两个控件之间的间距为0
    connect(mLayerView, SIGNAL(currentRowChanged(int)), this, SLOT(slotCurrentLayerSelected(int)));

    QHBoxLayout *opacityLayout = new QHBoxLayout;//水平排列
    mOpacitySlider->setRange(0, 100);//设置滑块的最小值和最大值
    mOpacitySlider->setEnabled(false);//设置未连接时不可用
    mOpacityLabel->setBuddy(mOpacitySlider);//将标签与滑块链接起来
    opacityLayout->addWidget(mOpacityLabel);
    opacityLayout->addWidget(mOpacitySlider);
    connect(mOpacitySlider, SIGNAL(valueChanged(int)), this, SLOT(slotSliderValueChanged(int)));//当值更改时

    QToolBar *buttonContainer = new QToolBar;//提供一个可移动面板包括一组控件
    buttonContainer->setFloatable(false);
    buttonContainer->setMovable(false);
    buttonContainer->setIconSize(QSize(16, 16));//设置图片大小

    mActionShowTiles = new QAction(this);
    mActionShowTiles->setShortcut(tr("Ctrl+Shift+T"));//给这个动作添加一个快捷方式
    mActionShowTiles->setIcon(QIcon(QLatin1String(":/layersdock/images/show_hide_others.png")));//设置图片

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

    QVBoxLayout *listAndToolBar = new QVBoxLayout;//垂直布局
    listAndToolBar->setSpacing(0);//控件与控件之间的边距为0
    listAndToolBar->addLayout(opacityLayout);//水平
    listAndToolBar->addWidget(mLayerView);//树
    listAndToolBar->addWidget(buttonContainer);//移动面板控件
    layout->addLayout(listAndToolBar);//垂直布局中的垂直布局

    setWidget(widget);//给浮动窗口添加窗口
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
