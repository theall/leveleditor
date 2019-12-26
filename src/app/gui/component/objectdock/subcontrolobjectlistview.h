#ifndef TSUBCONTROLOBJECTLISTVIEW_H
#define TSUBCONTROLOBJECTLISTVIEW_H

#include <QTableView>

class TSubcontrolObjectListView : public QTableView
{
public:
    TSubcontrolObjectListView(QWidget *parent=nullptr);
    ~TSubcontrolObjectListView();

    // QAbstractItemView interface
public:
    void setModel(QAbstractItemModel *model);

    // QAbstractItemView interface
public:
    void selectRow(int row);
};

#endif // TSUBCONTROLOBJECTLISTVIEW_H
