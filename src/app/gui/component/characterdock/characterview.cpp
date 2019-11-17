#include "characterview.h"
#include <QtMath>
#include <QResizeEvent>
#include <QGridLayout>

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
{
    setFlow(LeftToRight);//设置排列为从左向右排列
    setFrameShadow(QFrame::Plain);//为框架添加阴影
    setFrameShape(QFrame::NoFrame);//设置框架边线为什么都不做
}

TCharacterView::~TCharacterView()
{
    mButtonList.clear();
}

int TCharacterView::add(const QPixmap &face)
{
    QPushButton *button = new QPushButton(this);
    button->setCheckable(true);
    button->setIcon(QIcon(face));
    button->setIconSize(QSize(mIconSize, mIconSize));
    button->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    button->setMinimumSize(1, mIconSize);
    button->setMaximumSize(mIconSize, mIconSize);
    connect(button, SIGNAL(clicked(bool)), this, SLOT(slotOnFaceButtonToggled(bool)));
    mButtonList.append(button);
    QListWidgetItem *item = new QListWidgetItem(this);
    item->setSizeHint(QSize(mIconSize,mIconSize));
    setItemWidget(item, button);
    return mButtonList.size();
}

void TCharacterView::slotOnFaceButtonToggled(bool toggled)
{
    QPushButton *button = static_cast<QPushButton*>(sender());
    if(button) {
        if(toggled && mLastPushedButton) {
            mLastPushedButton->blockSignals(true);
            mLastPushedButton->setChecked(false);
            mLastPushedButton->blockSignals(false);
        }
        emit characterToggled(mButtonList.indexOf(button), toggled);
    }
    mLastPushedButton = button;
}

void TCharacterView::resizeEvent(QResizeEvent *)
{
    setWrapping(false);
    setWrapping(true);
}

