#ifndef TMAPSTAB_H
#define TMAPSTAB_H

#include <QEvent>
#include <QTabWidget>
#include "mapview.h"

class TMapsTab : public QTabWidget
{
    Q_OBJECT

public:
    explicit TMapsTab(QWidget *parent = Q_NULLPTR);
    ~TMapsTab();

    void setModel(QAbstractItemModel *model, const QModelIndex &index);

signals:
    void modelIndexDoubleClicked(const QModelIndex &index);

private:
    void retranslateUi();

    // QWidget interface
protected:
    void changeEvent(QEvent *) Q_DECL_OVERRIDE;
};

#endif // TMAPSTAB_H
