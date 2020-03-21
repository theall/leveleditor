#ifndef TMAPVIEW_H
#define TMAPVIEW_H

#include <QMenu>
#include <QListWidget>
#include <QAbstractItemModel>

class TMapView : public QListWidget
{
    Q_OBJECT

public:
    explicit TMapView(QWidget *parent = Q_NULLPTR);
    ~TMapView();

    void setModel(QAbstractItemModel *model, const QModelIndex &index);

signals:
    void modelIndexDoubleClicked(const QModelIndex &index);

private slots:
    void slotCustomContextMenuRequested(const QPoint &pos);
    void slotActionTriggered(QAction *open);

private:
    QPixmap mDefaultIcon;
    QAbstractItemModel *mModel;
    QModelIndex mParentIndex;
    QModelIndex mIndex;
    QMenu *mMenu;

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // TMAPVIEW_H
