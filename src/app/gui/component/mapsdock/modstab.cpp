#include "modstab.h"
#include "modstab/mapstab.h"

TModsTab::TModsTab(QWidget *parent) :
    QTabWidget(parent)
{
    setDocumentMode(true);//此属性保留是否以适合文档页的模式呈现选项卡小部件。
    setTabsClosable(false);//此属性保留是否自动将关闭按钮添加到每个选项卡。

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    resize(240, 320);
}

TModsTab::~TModsTab()
{

}

void TModsTab::setModel(QAbstractItemModel *model)
{
    if(!model)
        return;

    for(int i=0;i<model->rowCount();i++) {
        TMapsTab *mapsTab = new TMapsTab(this);
        connect(mapsTab,
                SIGNAL(modelIndexDoubleClicked(QModelIndex)),
                this,
                SIGNAL(modelIndexDoubleClicked(QModelIndex)));

        QModelIndex modelIndex = model->index(i, 0);
        mapsTab->setModel(model, modelIndex);
        addTab(mapsTab, model->data(modelIndex).toString());
    }
}
