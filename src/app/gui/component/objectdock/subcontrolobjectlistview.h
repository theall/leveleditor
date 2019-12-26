#ifndef TSUBCONTROLOBJECTLISTVIEW_H
#define TSUBCONTROLOBJECTLISTVIEW_H

#include <QTableView>

class TSubControlObjectListView : public QTableView
{
public:
    TSubControlObjectListView(QWidget *parent=nullptr);
    ~TSubControlObjectListView();

    // QAbstractItemView interface
public:
    void setModel(QAbstractItemModel *model);

    // QAbstractItemView interface
public:
    void selectRow(int row);
};

#endif // TSUBCONTROLOBJECTLISTVIEW_H
