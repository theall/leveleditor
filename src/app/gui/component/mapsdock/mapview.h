#ifndef TMAPVIEW_H
#define TMAPVIEW_H

#include <QListWidget>
#include "mapsviewmodel.h"

class TMapView : public QListWidget
{
    Q_OBJECT

public:
    explicit TMapView(QWidget *parent = Q_NULLPTR);
    ~TMapView();

    TMapBundle *mapBundle() const;
    void setMapBundle(TMapBundle *mapBundle);

private slots:
    void slotOnMapAdded(TMap *map, int);
    void slotOnMapRemoved(TMap *map, int index);

private:
    TMapBundle *mMapBundle;

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
};

#endif // TMAPVIEW_H
