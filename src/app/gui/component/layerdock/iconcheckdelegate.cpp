#include "iconcheckdelegate.h"

#include <QPainter>
#include <QKeyEvent>
#include <QMouseEvent>
#include <utils/utils.h>

TIconCheckDelegate::TIconCheckDelegate(IconType icon,
                                     bool exclusive,
                                     QObject *parent) :
    QItemDelegate(parent)
  , mExclusive(exclusive)
{
    switch (icon) {
    case Lock:
        mCheckedIcon.addFile(QLatin1String(":/layersdock/images/locked.png"));
        mUncheckedIcon.addFile(QLatin1String(":/layersdock/images/unlocked.png"));
        break;
    case Visibility:
        mCheckedIcon.addFile(QLatin1String(":/layersdock/images/visible.png"));
        mUncheckedIcon.addFile(QLatin1String(":/layersdock/images/hidden.png"));
        break;
    }

    setClipping(false);
}

int TIconCheckDelegate::exclusiveSectionWidth()
{
    return qRound(Utils::dpiScaled(22));
}

/**
 * Override in order to remove the checkbox area condition in case of
 * exclusively displaying a checkbox icon.
 */
bool TIconCheckDelegate::editorEvent(QEvent *event,
                                    QAbstractItemModel *model,
                                    const QStyleOptionViewItem &option,
                                    const QModelIndex &index)
{
    if (!mExclusive)
        return QItemDelegate::editorEvent(event, model, option, index);

    // make sure that the item is checkable
    Qt::ItemFlags flags = model->flags(index);
    if (!(flags & Qt::ItemIsUserCheckable) || !(option.state & QStyle::State_Enabled)
            || !(flags & Qt::ItemIsEnabled))
        return false;

    // make sure that we have a check state
    QVariant value = index.data(Qt::CheckStateRole);
    if (!value.isValid())
        return false;

    // make sure that we have the right event type
    if ((event->type() == QEvent::MouseButtonRelease)
            || (event->type() == QEvent::MouseButtonDblClick)
            || (event->type() == QEvent::MouseButtonPress)) {
        QMouseEvent *me = static_cast<QMouseEvent*>(event);
        if (me->button() != Qt::LeftButton)
            return false;

        // eat the double click events inside the check rect
        if ((event->type() == QEvent::MouseButtonPress)
                || (event->type() == QEvent::MouseButtonDblClick))
            return true;

    } else if (event->type() == QEvent::KeyPress) {
        if (static_cast<QKeyEvent*>(event)->key() != Qt::Key_Space
                && static_cast<QKeyEvent*>(event)->key() != Qt::Key_Select)
            return false;
    } else {
        return false;
    }

    Qt::CheckState state = static_cast<Qt::CheckState>(value.toInt());
    if (flags & Qt::ItemIsUserTristate)
        state = static_cast<Qt::CheckState>((state + 1) % 3);
    else
        state = (state == Qt::Checked) ? Qt::Unchecked : Qt::Checked;
    return model->setData(index, state, Qt::CheckStateRole);
}

void TIconCheckDelegate::drawCheck(QPainter *painter,
                                  const QStyleOptionViewItem &opt,
                                  const QRect &rect,
                                  Qt::CheckState state) const
{
    const QRect &r = mExclusive ? opt.rect : rect;
    const QIcon &icon = (state == Qt::Checked) ? mCheckedIcon : mUncheckedIcon;
    const QPixmap &pixmap = icon.pixmap(mExclusive ? Utils::smallIconSize() : r.size());

    QSize layoutSize = pixmap.size() / pixmap.devicePixelRatio();
    QRect targetRect(QPoint(0, 0), layoutSize);
    targetRect.moveCenter(r.center());

    painter->drawPixmap(targetRect, pixmap);
}

void TIconCheckDelegate::drawDisplay(QPainter *painter,
                                    const QStyleOptionViewItem &option,
                                    const QRect &rect,
                                    const QString &text) const
{
    if (mExclusive) // suppress rendering of selection on top of icon
        return;

    QItemDelegate::drawDisplay(painter, option, rect, text);
}

QSize TIconCheckDelegate::sizeHint(const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const
{
    if (mExclusive)
        return Utils::dpiScaled(QSize(22, 20));
    return QItemDelegate::sizeHint(option, index);
}
