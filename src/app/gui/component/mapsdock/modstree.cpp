#include "modstree.h"

TModsTree::TModsTree(QWidget *parent) :
    QTreeView(parent)
{

}

TModsTree::~TModsTree()
{

}

TMapsViewModel *TModsTree::mapsViewModel() const
{
    return mMapsViewModel;
}

void TModsTree::setMapsViewModel(TMapsViewModel *mapsViewModel)
{
    mMapsViewModel = mapsViewModel;
}

void TModsTree::slotOnModuleAdded(TModule *module)
{

}

void TModsTree::slotOnModuleRemoved(TModule *module, int index)
{

}

void TModsTree::retranslateUi()
{

}

void TModsTree::changeEvent(QEvent *event)
{
    if (event->type()==QEvent::LanguageChange)
    {
        retranslateUi();//update ui
    }

    QTreeView::changeEvent(event);
}
