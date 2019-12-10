#include "objectlistview.h"

#include <QTableView>

TObjectListView::TObjectListView(QWidget *parent):
    QTableView(parent)
{

}

TObjectListView::~TObjectListView()
{

}

void TObjectListView::setModel(QAbstractItemModel *model)
{
    QTableView::setModel(model);
}

