#ifndef OBJECTLISTVIEW_H
#define OBJECTLISTVIEW_H

#include <QMenu>
#include <QAction>
#include <QTableView>

class TObjectListView : public QTableView
{
     Q_OBJECT

public:
    TObjectListView(QWidget *parent=nullptr);
    ~TObjectListView();

    void setModel(QAbstractItemModel *model);
};

#endif // OBJECTLISTVIEW_H
