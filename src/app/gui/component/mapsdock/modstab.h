#ifndef TMODSTAB_H
#define TMODSTAB_H

#include <QTabWidget>
#include <QAbstractItemView>

class TModsTab : public QTabWidget
{
    Q_OBJECT

public:
    explicit TModsTab(QWidget *parent = Q_NULLPTR);
    ~TModsTab();

    void setModel(QAbstractItemModel *model);

private:
    //void setModel(QAbstractItemModel *model, const QModelIndex &parent);
};

#endif // TMODSTAB_H
