#include "mapview.h"
#include <QResizeEvent>

TMapView::TMapView(QWidget *parent) :
    QListWidget(parent)
{
    setWrapping(true);
    setFlow(QListView::LeftToRight);
    setMovement(QListView::Static);
    setViewMode(QListView::IconMode);
    setIconSize(QSize(48,48));
}

TMapView::~TMapView()
{

}

//TMapBundle *TMapView::mapBundle() const
//{
//    return mMapBundle;
//}

//void TMapView::setMapBundle(TMapBundle *mapBundle)
//{
//    if(mMapBundle == mapBundle)
//        return;

//    if(mMapBundle)
//        mMapBundle->disconnect(this);

//    clear();
//    mMapBundle = mapBundle;

//    if(mMapBundle) {
//        connect(mMapBundle, SIGNAL(mapAdded(TMap*,int)), this, SLOT(slotOnMapAdded(TMap*,int)));
//        connect(mMapBundle, SIGNAL(mapRemoved(TMap*,int)), this, SLOT(slotOnMapRemoved(TMap*,int)));
//    }
//    for(TMap *map : mMapBundle->mapList()) {
//        QListWidgetItem *item = new QListWidgetItem(this);
//        item->setText(map->name());
//        item->setIcon(map->thumbnail());
//        addItem(item);
//    }
//}

//void TMapView::slotOnMapAdded(TMap *map, int)
//{
//    if(!map)
//        return;

//    QListWidgetItem *item = new QListWidgetItem(this);
//    item->setText(map->name());
//    item->setIcon(map->thumbnail());
//    addItem(item);
//}

//void TMapView::slotOnMapRemoved(TMap *map, int index)
//{
//    if(!map)
//        return;

//    removeItemWidget(item(index));
//}

void TMapView::resizeEvent(QResizeEvent *event)
{
    event->accept();
    setWrapping(false);
    setWrapping(true);
}
