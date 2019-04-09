#ifndef TMAPSPROXYVIEW_H
#define TMAPSPROXYVIEW_H

#include <QWidget>
#include "modstab.h"
#include "modstree.h"
#include "mapsviewmodel.h"

class TMapsProxyView : public QWidget
{
public:
    enum ViewMode {
        Tree,
        Tab
    };

    explicit TMapsProxyView(QWidget *parent = Q_NULLPTR);
    ~TMapsProxyView();

    void setViewMode(const ViewMode &viewMode);
    void setMapsViewModel(TMapsViewModel *mapsViewModel);

private:
    ViewMode mViewMode;
    TModsTab *mModsTab;
    TModsTree *mModsTree;
    TMapsViewModel *mMapsViewModel;
};

#endif // TMAPSPROXYVIEW_H
