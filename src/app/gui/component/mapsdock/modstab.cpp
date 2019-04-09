#include "modstab.h"
#include "mapstab.h"

TModsTab::TModsTab(QWidget *parent) :
    QTabWidget(parent)
  , mMapsViewModel(nullptr)
{
    setDocumentMode(true);
    setTabsClosable(false);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    resize(240, 320);
}

TModsTab::~TModsTab()
{

}

void TModsTab::setMapsViewModel(TMapsViewModel *mapsViewModel)
{
    if(mMapsViewModel == mapsViewModel)
        return;

    if(mMapsViewModel)
        mMapsViewModel->disconnect(this);

    clear();
    mMapsViewModel = mapsViewModel;
    if(mMapsViewModel) {
        connect(mMapsViewModel, SIGNAL(moduleAdded(TModule*,int)), this, SLOT(slotOnModuleAdded(TModule*,int)));
        connect(mMapsViewModel, SIGNAL(moduleRemoved(TModule*,int)), this, SLOT(slotOnModuleRemoved(TModule*,int)));

        for(TModule *module : mMapsViewModel->moduleList()) {
            TMapsTab *mapsTab = new TMapsTab(this);
            mapsTab->setModule(module);
            addTab(mapsTab, module->name());
        }
    }
}

void TModsTab::slotOnModuleAdded(TModule *module, int index)
{
    if(!module)
        return;

    TMapsTab *mapsTab = new TMapsTab(this);
    mapsTab->setModule(module);
    if(index != -1) {
        insertTab(index, mapsTab, module->name());
    } else {
        addTab(mapsTab, module->name());
    }
}

void TModsTab::slotOnModuleRemoved(TModule *module, int index)
{
    if(!module)
        return;

    removeTab(index);
}
