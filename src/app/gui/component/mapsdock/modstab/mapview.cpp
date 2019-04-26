#include "mapview.h"
#include <QResizeEvent>

TMapView::TMapView(QWidget *parent) :
    QListWidget(parent)
{
    setWrapping(true);
    setFlow(QListView::LeftToRight);
    setMovement(QListView::Static);
    setViewMode(QListView::IconMode);
    setIconSize(QSize(128, 128));

    QPixmap pixmap(96, 48);
    pixmap.fill(Qt::transparent);
    mDefaultIcon = pixmap;
}

TMapView::~TMapView()
{

}

void TMapView::setModel(QAbstractItemModel *model, const QModelIndex &index)
{
    if(!model)
        return;

    mModel = model;
    mParentIndex = index;

    for(int i=0;i<model->rowCount(index);i++) {
        QListWidgetItem *item = new QListWidgetItem(this);
        QModelIndex modelIndex = model->index(i, 0, index);
        item->setText(model->data(modelIndex).toString());

        QPixmap icon = model->data(modelIndex, Qt::DecorationRole).value<QPixmap>();
        if(icon.isNull())
            icon = mDefaultIcon;

        int iconWidth = icon.width();
        if(iconWidth < 64)
            iconWidth = 64;

        int iconHeight = icon.height();
        if(iconHeight < 64)
            iconHeight = 64;

        item->setSizeHint(QSize(iconWidth,iconHeight+20));
        item->setIcon(icon);
        addItem(item);
    }
}

void TMapView::resizeEvent(QResizeEvent *event)
{
    event->accept();
    setWrapping(false);
    setWrapping(true);
}

void TMapView::mouseDoubleClickEvent(QMouseEvent *event)
{
    QAbstractItemModel *m = model();
    if(!m || !mModel)
        return;

    QModelIndex clickedIndex = indexAt(event->pos());
    clickedIndex = mModel->index(clickedIndex.row(), clickedIndex.column(), mParentIndex);
    emit modelIndexDoubleClicked(clickedIndex);
}
