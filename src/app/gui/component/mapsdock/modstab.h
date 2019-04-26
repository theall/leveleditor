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

signals:
    void modelIndexDoubleClicked(const QModelIndex &index);

private:

};

#endif // TMODSTAB_H
