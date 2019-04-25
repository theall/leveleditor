#ifndef TMAPSPROXYVIEW_H
#define TMAPSPROXYVIEW_H

#include <QWidget>
#include <QAbstractItemModel>
#include "modstab.h"
#include "modstree.h"

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
    void setModel(QAbstractItemModel *model);

private:
    ViewMode mViewMode;
    TModsTab *mModsTab;
    TModsTree *mModsTree;
};

#endif // TMAPSPROXYVIEW_H
