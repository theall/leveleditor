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
    QWidget(parent)
  , mCols(1)
  , mIconSize(ICON_SMALL)
  , mResizeIgnored(false)
  , mLastPushedButton(nullptr)
  , mBottomSpacer(new QSpacerItem(1, 2, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding))
  , mLeftSpacer(new QSpacerItem(2, 1, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum))
  , mRightSpacer(new QSpacerItem(2, 1, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum))
{
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->setContentsMargins(0, 0, 0, 0);
    gridLayout->setMargin(ICON_MARGIN);
    gridLayout->setSpacing(0);
    gridLayout->setHorizontalSpacing(ICON_MARGIN);
    gridLayout->setVerticalSpacing(ICON_MARGIN);
    gridLayout->addItem(mBottomSpacer, 1, 0);
    gridLayout->addItem(mLeftSpacer, 0, 0);
    gridLayout->addItem(mRightSpacer, 0, mCols+1);
    setLayout(gridLayout);
    calcRowsAndCols();
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
    button->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    button->setMinimumSize(1, mIconSize);
    button->setMaximumSize(mIconSize, mIconSize);
    connect(button, SIGNAL(clicked(bool)), this, SLOT(slotOnFaceButtonToggled(bool)));
    mButtonList.append(button);
    int buttonCount = mButtonList.size();
    QGridLayout *gridLayout = static_cast<QGridLayout*>(layout());
    if(gridLayout) {
        bool needRemove = (buttonCount-1)%mCols==0;
        int row = qFloor((float)buttonCount/mCols);
        if(needRemove)
            gridLayout->removeItem(mBottomSpacer);
        gridLayout->addWidget(button, row, buttonCount%mCols+1);
        if(needRemove)
            gridLayout->addItem(mBottomSpacer, row+1, 0);
    }
    return buttonCount;
}

void TCharacterView::calcRowsAndCols()
{
    QSize currentSize = size();
    int newCols = (currentSize.width() - 1 + ICON_MARGIN - mLeftSpacer->minimumSize().width() - mRightSpacer->minimumSize().width()) / (mIconSize + ICON_MARGIN);
    if(newCols <= 0)
        newCols = 1;

    if(newCols != mCols) {
        if(newCols > mCols) {
            currentSize.setHeight(qCeil((float)mButtonList.size() / mCols) * (mIconSize + ICON_MARGIN));
            resize(currentSize);
        }
        mCols = newCols;
        reArrange();
    }
}

void TCharacterView::reArrange()
{
    QGridLayout *gridLayout = static_cast<QGridLayout*>(layout());
    if(gridLayout && !mButtonList.isEmpty()) {
        for(QPushButton *button : mButtonList) {
            gridLayout->removeWidget(button);
        }
        gridLayout->removeItem(mLeftSpacer);
        gridLayout->removeItem(mRightSpacer);
        gridLayout->removeItem(mBottomSpacer);

        int rows = qCeil((float)mButtonList.size() / mCols);
        int index = 0;
        for(int r=0;r<rows;r++) {
            for(int c=1;c<=mCols;c++) {
                QPushButton *button = mButtonList.at(index);
                gridLayout->addWidget(button, r, c);
                index++;
                if(index >= mButtonList.size())
                    break;
            }
        }
        gridLayout->addItem(mBottomSpacer, rows, 0);
        gridLayout->addItem(mLeftSpacer, 0, 0);
        gridLayout->addItem(mRightSpacer, 0, mCols+1);

        mResizeIgnored = true;
    }
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

void TCharacterView::resizeEvent(QResizeEvent *event)
{
    event->accept();
    if(mResizeIgnored)
    {
        mResizeIgnored = false;
        return;
    }

    calcRowsAndCols();
}

void TCharacterView::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

#ifdef GUI_STAND_ALONE
    QPainter p(this);
    p.drawRect(rect());
#endif
}
