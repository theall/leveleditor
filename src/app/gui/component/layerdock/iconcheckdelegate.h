#ifndef ICONCHECKDELEGATE_H
#define ICONCHECKDELEGATE_H

#include <QIcon>
#include <QItemDelegate>


/**
 * Delegate for drawing an icon in layer view for displaying
 * visibility and locked state.
 */
class TIconCheckDelegate : public QItemDelegate
{
public:
    enum IconType {
        Lock,
        Visibility
    };

    explicit TIconCheckDelegate(IconType icon,
                               bool exclusive,
                               QObject *parent = nullptr);

    static int exclusiveSectionWidth();

    bool editorEvent(QEvent *event,
                     QAbstractItemModel *model,
                     const QStyleOptionViewItem &option,
                     const QModelIndex &index) override;

protected:
    void drawCheck(QPainter *painter,
                   const QStyleOptionViewItem &option,
                   const QRect &rect,
                   Qt::CheckState state) const override;

    void drawDisplay(QPainter *painter,
                     const QStyleOptionViewItem &option,
                     const QRect &rect,
                     const QString &text) const override;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;


private:
    QIcon mCheckedIcon;
    QIcon mUncheckedIcon;
    bool mExclusive;
};
#endif //ICONCHECKDELEGATE_H
