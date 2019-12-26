#include "characterview.h"
#include <QtMath>
#include <QResizeEvent>
#include <QGridLayout>

#include <QMouseEvent>
#include <QHeaderView>
#include <QContextMenuEvent>

#ifdef GUI_STAND_ALONE
#include <QDebug>
#include <QPainter>
#endif

#define ICON_SMALL 32
#define ICON_LARGE 64
#define ICON_MARGIN 0

TCharacterView::TCharacterView(QWidget *parent) :
    QListWidget(parent)
  , mIconSize(ICON_LARGE)
  , mLastPushedButton(nullptr)
  , mContextMenu(new QMenu(this))
{
    setFlow(LeftToRight);//设置排列为从左向右排列
    setFrameShadow(QFrame::Plain);//为框架添加阴影QFrame::Plain
    setFrameShape(QFrame::NoFrame);//设置框架边线为什么都不做
    //connect(mShow, SIGNAL(triggered(bool)), this, SLOT(slotActionShowTriggered(bool)));//开眼
    //connect(mHide, SIGNAL(triggered(bool)), this, SLOT(slotActionHideTriggered(bool)));//关眼

    retranslateUi();
}

TCharacterView::~TCharacterView()
{
    clear();
}

int TCharacterView::add(const QPixmap &face, int id)
{
    QPushButton *button = new QPushButton(this);
    button->setCheckable(true);
    button->setIcon(QIcon(face));
    button->setIconSize(QSize(mIconSize, mIconSize));
    button->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    button->setMinimumSize(1, mIconSize);
    button->setMaximumSize(mIconSize, mIconSize);
    button->setToolTip(QString::asprintf("%1", id));
    connect(button, SIGNAL(clicked(bool)), this, SLOT(slotOnFaceButtonToggled(bool)));
    mButtonList.append(button);
    QListWidgetItem *item = new QListWidgetItem(this);
    item->setSizeHint(QSize(mIconSize,mIconSize));
    setItemWidget(item, button);
    //button->setEnabled(false);
    return mButtonList.size();
}

void TCharacterView::getButton(bool button) const
{
    //return button;
}

void TCharacterView::setPixmapSet(const QList<QPixmap> &pixmapSet, const QList<int> &idList)
{
    clear();

    if(!idList.isEmpty())
        Q_ASSERT(pixmapSet.size()==idList.size());

    for(int i=0;i<pixmapSet.size();i++) {
        add(pixmapSet.at(i), idList.at(i));
    }
}

void TCharacterView::clear()
{
    QListWidget::clear();
    mButtonList.clear();
    mButtonValueMap.clear();
}

void TCharacterView::slotOnFaceButtonToggled(bool toggled)
{
    QPushButton *button = static_cast<QPushButton*>(sender());
    if(button) {
        if(toggled && mLastPushedButton) {
            mLastPushedButton->blockSignals(true);
            mLastPushedButton->setChecked(false);
            mLastPushedButton->blockSignals(false);
            //button->setEnabled(true);
        }
        emit buttonPushed(mButtonList.indexOf(button));
    }
    mLastPushedButton = button;
}

void TCharacterView::resizeEvent(QResizeEvent *)
{
    setWrapping(false);
    setWrapping(true);
}

void TCharacterView::contextMenuEvent(QContextMenuEvent *event)
{
    mContextMenu->popup(event->globalPos());
}

void TCharacterView::retranslateUi()
{

}

