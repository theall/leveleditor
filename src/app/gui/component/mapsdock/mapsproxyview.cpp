#include "mapsproxyview.h"
#include <QVBoxLayout>

TMapsProxyView::TMapsProxyView(QWidget *parent) :
    QWidget(parent)
  , mViewMode(Tree)
  , mModsTab(new TModsTab(this))
  , mModsTree(new TModsTree(this))
{
    QVBoxLayout *vboxLayout = new QVBoxLayout;
    vboxLayout->addWidget(mModsTab);
    vboxLayout->addWidget(mModsTree);
    vboxLayout->setContentsMargins(0, 0, 0, 0);
    vboxLayout->setMargin(0);
    vboxLayout->setSpacing(0);
    setLayout(vboxLayout);

    setViewMode(Tab);

#ifdef GUI_STAND_ALONE
    TMapsViewModel *model = new TMapsViewModel(this);
    TModule *module = new TModule(model);
    TMapBundle *advBundle;
    TMapBundle *ctfBundle;
    TMapBundle *vsBundle;
    QPixmap pixmap;
    pixmap.load(":/mapsdock/images/tree.png");

    advBundle = module->getAdvBundle();
    vsBundle = module->getVsBundle();
    ctfBundle = module->getCtfBundle();
    module->setName("original");
    for(int i=0;i<52;i++) {
        TMap *map = new TMap(advBundle);
        map->setName(QString("amap%1").arg(i+1));
        map->setThumbnail(pixmap);
        advBundle->add(map);
    }
    for(int i=0;i<20;i++) {
        TMap *map = new TMap(vsBundle);
        map->setName(QString("map%1").arg(i+1));
        map->setThumbnail(pixmap);
        vsBundle->add(map);
    }
    for(int i=0;i<4;i++) {
        TMap *map = new TMap(ctfBundle);
        map->setName(QString("CTF_map%1").arg(i+1));
        map->setThumbnail(pixmap);
        ctfBundle->add(map);
    }
    model->add(module);

    module = new TModule(model);
    module->setName("rainbow");
    advBundle = module->getAdvBundle();
    vsBundle = module->getVsBundle();
    ctfBundle = module->getCtfBundle();
    for(int i=0;i<40;i++) {
        TMap *map = new TMap(advBundle);
        map->setName(QString("amap%1").arg(i+1));
        map->setThumbnail(pixmap);
        advBundle->add(map);
    }
    for(int i=0;i<10;i++) {
        TMap *map = new TMap(vsBundle);
        map->setName(QString("map%1").arg(i+1));
        map->setThumbnail(pixmap);
        vsBundle->add(map);
    }
    for(int i=0;i<8;i++) {
        TMap *map = new TMap(ctfBundle);
        map->setName(QString("CTF_map%1").arg(i+1));
        map->setThumbnail(pixmap);
        ctfBundle->add(map);
    }
    model->add(module);

    setMapsViewModel(model);
#endif
}

TMapsProxyView::~TMapsProxyView()
{

}

void TMapsProxyView::setViewMode(const TMapsProxyView::ViewMode &viewMode)
{
    if(mViewMode == viewMode)
        return;

    mViewMode = viewMode;
    if(mViewMode == Tree) {
        mModsTab->setVisible(false);
        mModsTree->setVisible(true);
    } else if(mViewMode == Tab) {
        mModsTab->setVisible(true);
        mModsTree->setVisible(false);
    }
}

void TMapsProxyView::setMapsViewModel(TMapsViewModel *mapsViewModel)
{
    if(mMapsViewModel == mapsViewModel)
        return;

    mMapsViewModel = mapsViewModel;
    mModsTab->setMapsViewModel(mapsViewModel);
    mModsTree->setMapsViewModel(mapsViewModel);
}
