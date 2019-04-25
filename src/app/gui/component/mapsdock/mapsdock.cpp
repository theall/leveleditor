#include "mapsdock.h"

#include <QSplitter>
#include <QVBoxLayout>

TMapsDock::TMapsDock(QWidget *parent) :
    TBaseDock(QLatin1String("MapsDock"), parent)
  , mMapsProxyView(new TMapsProxyView(this))
{
    CREATE_ACTION_TOGGLED(mActionShowTreeView, ":/mapsdock/images/tree.png", slotActionShowTreeViewToggled);

    QToolBar *toolBar = new QToolBar(this);
    toolBar->setFloatable(false);
    toolBar->setMovable(false);
    toolBar->setIconSize(QSize(16, 16));
    toolBar->addAction(mActionShowTreeView);

    QWidget *container = new QWidget(this);
    QSplitter *splitter = new QSplitter(this);
    splitter->setOrientation(Qt::Vertical);
    splitter->addWidget(mMapsProxyView);
    QVBoxLayout *vBoxLayout = new QVBoxLayout;
    vBoxLayout->setContentsMargins(2, 2, 2, 2);
    vBoxLayout->setSpacing(0);
    vBoxLayout->addWidget(toolBar);
    vBoxLayout->addWidget(splitter);
    container->setLayout(vBoxLayout);
    setWidget(container);

    mActionShowTreeView->setChecked(false);
    retranslateUi();
}

TMapsDock::~TMapsDock()
{

}

void TMapsDock::slotActionShowTreeViewToggled(bool checked)
{
    mMapsProxyView->setViewMode(checked?TMapsProxyView::Tree:TMapsProxyView::Tab);
}

TMapsProxyView *TMapsDock::mapsProxyView() const
{
    return mMapsProxyView;
}

void TMapsDock::retranslateUi()
{
    setWindowTitle(tr("Maps"));
    setToolTip(tr("Maps manager."));

    if(mActionShowTreeView->isChecked()) {
        mActionShowTreeView->setToolTip(tr("Toggle to show tab view."));
        mActionShowTreeView->setText(tr("Tab view"));
    } else {
        mActionShowTreeView->setToolTip(tr("Toggle to show tree view."));
        mActionShowTreeView->setText(tr("Tree view"));
    }
}
