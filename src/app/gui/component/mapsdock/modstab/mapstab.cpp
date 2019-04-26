#include "mapstab.h"

TMapsTab::TMapsTab(QWidget *parent) :
    QTabWidget(parent)
{
    setDocumentMode(true);
    setTabsClosable(false);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    resize(240, 320);

    retranslateUi();
}

TMapsTab::~TMapsTab()
{

}

void TMapsTab::setModel(QAbstractItemModel *model, const QModelIndex &index)
{
    if(!model)
        return;

    for(int i=0;i<model->rowCount(index);i++) {
        TMapView *mapView = new TMapView(this);
        connect(mapView,
                SIGNAL(modelIndexDoubleClicked(QModelIndex)),
                this,
                SIGNAL(modelIndexDoubleClicked(QModelIndex)));

        QModelIndex modelIndex = model->index(i, 0, index);
        mapView->setModel(model, modelIndex);
        addTab(mapView, model->data(modelIndex).toString());
    }
}

void TMapsTab::changeEvent(QEvent *event)
{
    if (event->type()==QEvent::LanguageChange)
    {
        retranslateUi();//update ui
    }

    QTabWidget::changeEvent(event);
}

void TMapsTab::retranslateUi()
{

}
