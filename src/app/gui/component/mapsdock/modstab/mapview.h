#ifndef TMAPVIEW_H
#define TMAPVIEW_H

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

private:
    QPixmap mDefaultIcon;
    QAbstractItemModel *mModel;
    QModelIndex mParentIndex;

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // TMAPVIEW_H
