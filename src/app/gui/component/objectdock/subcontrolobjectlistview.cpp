#include "subcontrolobjectlistview.h"

#include <QHeaderView>

TSubControlObjectListView::TSubControlObjectListView(QWidget *parent)
{
    horizontalHeader()->setStretchLastSection(false);
    horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    horizontalHeader()->setVisible(false);
    verticalHeader()->setVisible(false);


}
TSubControlObjectListView::~TSubControlObjectListView()
{

}

void TSubControlObjectListView::setModel(QAbstractItemModel *model)
{
    QTableView::setModel(model);
}

void TSubControlObjectListView::selectRow(int row)
{
    QTableView::selectRow(row);
}
