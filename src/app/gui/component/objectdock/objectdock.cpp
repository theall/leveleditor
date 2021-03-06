#include "objectdock.h"

TObjectDock::TObjectDock(QWidget *parent) :
    TBaseDock(QLatin1String("Object"), parent)
  , mObjectcontainer(new TObjectContainer(this))
{
    setWidget(mObjectcontainer);
    retranslateUi();
}

TObjectDock::~TObjectDock()
{

}

void TObjectDock::retranslateUi()
{
    setWindowTitle(tr("Object"));
}

TObjectListView *TObjectDock::getObjectListView() const
{
    return mObjectcontainer->getobjectListView();
}

TSubControlObjectListView *TObjectDock::getSubControlObjectListView() const
{
    return mObjectcontainer->getSubControlObjectListView();
}
