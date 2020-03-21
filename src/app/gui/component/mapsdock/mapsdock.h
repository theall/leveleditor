#ifndef MAPSDOCK_H
#define MAPSDOCK_H

#include <QAction>
#include <QToolBar>
#include <QMenu>

#include "../basedock.h"
#include "mapsproxyview.h"

class TMapsDock : public TBaseDock
{
    Q_OBJECT

public:
    TMapsDock(QWidget *parent = nullptr);
    ~TMapsDock();

    TMapsProxyView *mapsProxyView() const;

signals:
    void modelIndexDoubleClicked(const QModelIndex &index);

private slots:
    void slotActionShowTreeViewToggled(bool);

private:
    QAction *mActionShowTreeView;
    TMapsProxyView *mMapsProxyView;
    // TBaseDock interface
public:
    void retranslateUi() Q_DECL_OVERRIDE;
};

#endif // MAPSDOCK_H
