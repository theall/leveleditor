#include "mapstab.h"

#define INDEX_ADV   0
#define INDEX_VS    1
#define INDEX_CTF   2
TMapsTab::TMapsTab(QWidget *parent) :
    QTabWidget(parent)
//  , mModule(nullptr)
  , mAdvView(new TMapView(this))
  , mCtfView(new TMapView(this))
  , mVsView(new TMapView(this))
{
    setDocumentMode(true);
    setTabsClosable(false);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    resize(240, 320);

    addTab(mAdvView, QString());
    addTab(mVsView, QString());
    addTab(mCtfView, QString());

    retranslateUi();
}

TMapsTab::~TMapsTab()
{

}

//TModule *TMapsTab::module() const
//{
//    return mModule;
//}

//void TMapsTab::setModule(TModule *module)
//{
//    if(mModule == module)
//        return;

//    mModule = module;
//    mAdvView->setMapBundle(module->getAdvBundle());
//    mCtfView->setMapBundle(module->getCtfBundle());
//    mVsView->setMapBundle(module->getVsBundle());
//}

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
    setTabText(INDEX_ADV, tr("ADV"));
    setTabText(INDEX_VS, tr("VS"));
    setTabText(INDEX_CTF, tr("CTF"));
}
