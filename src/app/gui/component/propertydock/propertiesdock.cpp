#include "propertiesdock.h"

#include <QToolBar>
#include <QVBoxLayout>
#include <QHBoxLayout>

TPropertiesDock::TPropertiesDock(QWidget *parent) :
    TBaseDock("propertiesDock", parent)
  , mIcon(new QLabel(this))//标签
  , mText(new QLabel(this))
  , mSearchLabel(new QLabel(this))
  , mFindWhat(new QLineEdit(this))//单行文本编辑器
  , mFindWidgetsWrap(new QWidget(this))//窗口
  , mPropertyBrowser(new TPropertyBrowser(this))//窗口
{
    mIcon->setFixedSize(24, 24);
    mIcon->setVisible(false);

    QFont ft= mText->font();
    ft.setPixelSize(12);
    ft.setBold(true);
    mText->setFixedHeight(24);
    mText->setFont(ft);
    mText->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    mFindWhat->setClearButtonEnabled(true);
    connect(mFindWhat, SIGNAL(textChanged(QString)), this, SLOT(slotFindWhatChanged(QString)));

    QToolBar *toolBar = new QToolBar;
    toolBar->setFloatable(false);
    toolBar->setMovable(false);
    toolBar->setIconSize(QSize(16, 16));
    mActionSearch = toolBar->addAction("");
    mActionSearch->setCheckable(true);
    mActionSearch->setIcon(QIcon(":/toolbar/images/find.png"));
    connect(mActionSearch, SIGNAL(triggered(bool)), this, SLOT(slotSearchActionTriggered(bool)));

    mActionConfig = toolBar->addAction(tr("C"));
    mActionConfig->setIcon(QIcon(":/toolbar/images/setting.png"));

    QHBoxLayout *toolBarLayout = new QHBoxLayout;
    toolBarLayout->setSpacing(0);
    toolBarLayout->setMargin(0);
    toolBarLayout->addWidget(mIcon);
    toolBarLayout->addWidget(mText);
    toolBarLayout->addWidget(toolBar);

    QHBoxLayout *findLayout = new QHBoxLayout;
    findLayout->setSpacing(0);
    findLayout->setMargin(0);
    findLayout->addWidget(mSearchLabel);
    findLayout->addWidget(mFindWhat);
    mFindWidgetsWrap->setLayout(findLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(2);
    mainLayout->setSpacing(0);
    mainLayout->addLayout(toolBarLayout);
    mainLayout->addWidget(mFindWidgetsWrap);
    mainLayout->addWidget(mPropertyBrowser);

    QWidget *widget = new QWidget(this);
    widget->setLayout(mainLayout);

    setWidget(widget);

    mFindWidgetsWrap->setVisible(false);
    retranslateUi();
}

TPropertiesDock::~TPropertiesDock()
{

}

void TPropertiesDock::bringToFront()
{
    show();
    raise();
    mPropertyBrowser->setFocus();
}

void TPropertiesDock::slotSearchActionTriggered(bool checked)
{
    mFindWidgetsWrap->setVisible(checked);
    if(checked)
    {
        mFindWhat->setFocus();
        mFindWhat->selectAll();
    }
}

void TPropertiesDock::slotFindWhatChanged(const QString &text)
{
    mPropertyBrowser->setFilter(text);
}

TPropertyBrowser *TPropertiesDock::propertyBrowser() const
{
    return mPropertyBrowser;
}

void TPropertiesDock::setText(const QString &text)
{
    mText->setText(text);
}

void TPropertiesDock::setIcon(const QPixmap &icon)
{
    mIcon->setPixmap(icon);
}

void TPropertiesDock::retranslateUi()
{
    setWindowTitle(tr("Properties"));

    mSearchLabel->setText(tr("Filter:"));
    mActionSearch->setText(tr("Search"));
}
