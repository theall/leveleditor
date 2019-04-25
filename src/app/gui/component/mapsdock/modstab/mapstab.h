#ifndef TMAPSTAB_H
#define TMAPSTAB_H

#include <QEvent>
#include <QTabWidget>
#include "mapview.h"

class TMapsTab : public QTabWidget
{
public:
    explicit TMapsTab(QWidget *parent = Q_NULLPTR);
    ~TMapsTab();

//    TModule *module() const;
//    void setModule(TModule *module);

private:
//    TModule *mModule;
    TMapView *mAdvView;
    TMapView *mCtfView;
    TMapView *mVsView;

    void retranslateUi();

    // QWidget interface
protected:
    void changeEvent(QEvent *) Q_DECL_OVERRIDE;
};

#endif // TMAPSTAB_H
